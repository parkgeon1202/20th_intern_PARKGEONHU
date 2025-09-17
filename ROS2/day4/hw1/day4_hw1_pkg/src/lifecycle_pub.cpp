#include "day4_hw1_pkg/lifecycle_pub.hpp"
    pub_cycle::pub_cycle(): rclcpp_lifecycle::LifecycleNode("publisher"), count_(0){}; //노드 이름 설정

    rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn pub_cycle:: on_configure(const rclcpp_lifecycle::State &)
    {   
        rclcpp::QoS qos(10); //qos설정을 위해 qos 객체 생성
	    qos.reliability(RMW_QOS_POLICY_RELIABILITY_RELIABLE); // reliability 설정, subscribe노드의 reliablility 호환을 맞추기 위해
        qos.durability(RMW_QOS_POLICY_DURABILITY_TRANSIENT_LOCAL);//이 또한 호환되도록 만들고자 설정
        pub_ptr = this->create_publisher<std_msgs::msg::String>("topic", qos); //토픽명 설정, qos 대입
        timer_ = this->create_wall_timer(1s, std::bind(&pub_cycle::timer_callback, this)); //configure된 것이라면 이전처럼 타이머 설정하여 1초마다 publish하도록 함

        RCLCPP_INFO(this->get_logger(), "on_configure() is called");

        return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;
    }

    rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn pub_cycle::on_activate(const rclcpp_lifecycle::State &)
    {

        pub_ptr->on_activate();

        RCLCPP_INFO(this->get_logger(), "activate is called");

        return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;
    }

    rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn pub_cycle::on_deactivate(const rclcpp_lifecycle::State &)
    {
        pub_ptr->on_deactivate();
        RCLCPP_INFO(this->get_logger(), "deactivate is called");
       

        return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;
    }

    rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn pub_cycle::on_cleanup(const rclcpp_lifecycle::State &)
    {

        timer_.reset(); //shared_ptr이기에 reset하여 타이머 또한 멈추도록 함. configure가 해제되기에 타이머 멈추고 publish하면 안 됨
        pub_ptr.reset();//publisher 객체 해제 
        RCLCPP_INFO(this->get_logger(), "cleanup is called");
        

        return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;
    }

    rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn pub_cycle::on_shutdown(const rclcpp_lifecycle::State &)
    {

        timer_.reset(); //cleanup과 똑같이
        pub_ptr.reset();
        RCLCPP_INFO(this->get_logger(), "shutdown is called");
        

        return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;
    }
void pub_cycle::timer_callback()
    {   //데이터 생성
        auto message = std_msgs::msg::String();
        message.data = "Creating a map " + std::to_string(count_++); //ros2 기본 예제처럼 구성
        
        if (!pub_ptr->is_activated())
        {
            RCLCPP_INFO(
                get_logger(), "inactive.not published.");
        }
        else
        {
            RCLCPP_INFO(get_logger(), "active!! Publishing: [%s]", message.data.c_str()); //띄울 메시지 출력
        }

        pub_ptr->publish(message);
    }

    