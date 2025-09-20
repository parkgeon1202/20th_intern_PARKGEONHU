#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/joy.hpp>
#include <geometry_msgs/msg/twist.hpp>


class joy_subscribe: public rclcpp::Node{
    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr sub_ptr; //joy_node로부터 값 받아오기 위해
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr pub_ptr; //받아온 값을 cmd/vel로 보내야 하기에 cmd_vel 토픽의 타입으로 publisher 생성
    public:
    joy_subscribe(); 
    void msg_callback(const sensor_msgs::msg::Joy::SharedPtr msg); //메시지 받았을 때의 콜백함수, 메시지 받아서 바로 publish 함

};
