
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "rclcpp_lifecycle/lifecycle_node.hpp"
class sub_cycle : public rclcpp_lifecycle::LifecycleNode
{
public:
    sub_cycle();
    //오버라이딩
    rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
    on_configure(const rclcpp_lifecycle::State &);

    rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
    on_activate(const rclcpp_lifecycle::State &);

    rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
    on_deactivate(const rclcpp_lifecycle::State &);

    rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
    on_cleanup(const rclcpp_lifecycle::State &);

    rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
    on_shutdown(const rclcpp_lifecycle::State &);

private:
    void topic_callback(const std_msgs::msg::String &msg) const;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;//Lifecycle의 전용 subscription이 없어서 이를 그대로 사용. 대신 상속받아서 오버라이딩하여 터미널 출력을 하도록 함
    bool m_isActivated = false; //별도의 특별 subscription이 없어서 lifecycle의 인터페이스를 그대로 쓰며 이 때 flag를 사용하여 더 스마트하게 쓰고자 함
};