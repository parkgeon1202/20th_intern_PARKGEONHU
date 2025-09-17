#include "day4_hw1_pkg/lifecycle_sub.hpp"
    sub_cycle::sub_cycle(): rclcpp_lifecycle::LifecycleNode("subscriber") {}; //노드명 정하기

    rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
    sub_cycle::on_configure(const rclcpp_lifecycle::State &) //on_configure 오버라이딩 
    {
        rclcpp::QoS qos_subscriber(10); //qos 객체 생성함
        qos_subscriber.reliability(RMW_QOS_POLICY_RELIABILITY_RELIABLE); //모든 publish에서 오는 메시지 다 받도록 설정
        qos_subscriber.durability(RMW_QOS_POLICY_DURABILITY_TRANSIENT_LOCAL); //publish로부터 받은 메시지 기억하도록 설정
        subscription_ = this->create_subscription<std_msgs::msg::String>(
            "topic", qos_subscriber, std::bind(&sub_cycle::topic_callback, this, std::placeholders::_1)); //토픽명 설정 및 qos객체 넣기
        m_isActivated = false;
        RCLCPP_INFO(this->get_logger(), "configure() is called");

        return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;
    }

    rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
    sub_cycle::on_activate(const rclcpp_lifecycle::State &)
    {
        m_isActivated = true; //activate 되는 flag 설정, 이것을 flag로 하여 publish메서드 사용
        RCLCPP_INFO(this->get_logger(), "activate is called"); 

        return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;
    }

    rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
    sub_cycle::on_deactivate(const rclcpp_lifecycle::State &)
    {
        m_isActivated = false; //active 해제되니 false로 변경
        RCLCPP_INFO(this->get_logger(), "deactivate is called");

        return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;
    }

    rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
    sub_cycle::on_cleanup(const rclcpp_lifecycle::State &)
    {
        subscription_.reset();  //shared_ptr메서드를 통해 메모리 해제 및 nullptr초기화 
        RCLCPP_INFO(this->get_logger(), "cleanup is called");

        return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;
    }

    rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
    sub_cycle::on_shutdown(const rclcpp_lifecycle::State &)
    {
        subscription_.reset(); //shared_ptr메서드를 통해 메모리 해제 및 nullptr초기화
        RCLCPP_INFO(this->get_logger(), "shutdown is called");
        return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;
    }
    void sub_cycle::topic_callback(const std_msgs::msg::String &msg) const
    {
        if (m_isActivated) //active인 경우
        {
            RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg.data.c_str()); //콜백함수로, 받은 메시지 처리
        }
        else
        {
            RCLCPP_INFO(
                get_logger(), "inactive");
        }
    }