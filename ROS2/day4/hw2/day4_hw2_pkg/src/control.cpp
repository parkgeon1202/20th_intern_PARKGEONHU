#include <rclcpp/rclcpp.hpp>
#include "control.hpp"

joy_subscribe::joy_subscribe():Node("sub_and_pub"){ //노드명 잡기
    pub_ptr = create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10); //cmd_vel에게 토픽보내기
    sub_ptr = create_subscription<sensor_msgs::msg::Joy>("/joy", 10, std::bind(&joy_subscribe::msg_callback, this, std::placeholders::_1)); // joy토픽으로부터 값 받는 것 설정
}   
void joy_subscribe::msg_callback(const sensor_msgs::msg::Joy::SharedPtr msg){ //joy토픽으로부터 받은 값을 처리해서 cmd_vel로 바로 보냄
    geometry_msgs::msg::Twist value;
    
    value.linear.x = msg->axes[1] * 1.0; //받은 선속도를 cmd_vel 타입의 객체에 대입
    value.angular.z = msg->axes[3] * 1.0; //받은 각속도를 대입
    // 조이스틱에서 온 값은 단위가 없기에 1.0을 곱하여 1m/s, 1rad/s라는 단위를 붙여주는 의미를 주기 위해 1.0을 곱함
    pub_ptr->publish(value); //해당 타입 객체를 퍼블리시
}


