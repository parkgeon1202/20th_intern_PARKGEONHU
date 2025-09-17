#include <chrono>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "rclcpp_lifecycle/lifecycle_node.hpp"

using namespace std::chrono_literals; //1s를 쓰기 위해 

// class pub_cycle : public rclcpp::Node
class pub_cycle : public rclcpp_lifecycle::LifecycleNode
{
public:
    pub_cycle();
    //LifecycleNode 메서드 오버라이딩, 오버라이딩을 사용하기 위해 매개변수를 꼭 const rclcpp_lifecycle::State &으로 써줘야 함
    rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn on_configure(const rclcpp_lifecycle::State &);

    rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn on_activate(const rclcpp_lifecycle::State &);

    rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn on_deactivate(const rclcpp_lifecycle::State &);

    rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn on_cleanup(const rclcpp_lifecycle::State &);

    rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn on_shutdown(const rclcpp_lifecycle::State &);

private:
    void timer_callback(); //1초마다 publish하기 위함
    rclcpp::TimerBase::SharedPtr timer_; //ros2 강의자료 예제의 타이머 사용
    std::shared_ptr<rclcpp_lifecycle::LifecyclePublisher<std_msgs::msg::String>> pub_ptr;//SharedPtr 멤버가 없어서 shared_ptr로 덮어서 사용
    size_t count_; //터미널 출력, 메시지를 매번 바꾸기 위해
};
