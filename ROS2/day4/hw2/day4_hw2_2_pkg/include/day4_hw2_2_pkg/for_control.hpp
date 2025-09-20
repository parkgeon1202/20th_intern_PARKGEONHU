#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include "tf2_ros/transform_broadcaster.h"
#include "geometry_msgs/msg/transform_stamped.hpp"
class controlling: public rclcpp::Node{
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr sub_ptr; //day4_hw2_pkg에서 보낸 토픽을 그대로 받고 
    std::shared_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster; //tf_broadcaster로 보냄
    double x; //transformStamped에서 x, y, z를 설정해야 하고 2차원으로 움직이기에 이를 위한 x, y
    double y;
    double angle; //각도를 yaw로 줘야 하므로  
    double linear_v; //메시지로부터 받은 선속도
    double angular_v; //메시지로부터 받은 각속도
    rclcpp::TimerBase::SharedPtr timer_; //타이머를 통해 매번 거리 이동 최신화
    public:
    controlling();
    void msg_callback(const geometry_msgs::msg::Twist::SharedPtr msg); //메시지 콜백 메서드
    void timer_callback();//타임아웃될 때마다 호출되는 콜백 메서드

};