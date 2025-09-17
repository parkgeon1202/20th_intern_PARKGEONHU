#include <rclcpp/rclcpp.hpp>
#include "custom_interfaces/msg/colcon.hpp" // 사용자 정의한 메시지 타입 헤더 파일 포함

class publisher : public rclcpp::Node //퍼블리셔
{
    
    rclcpp::Publisher<custom_interfaces::msg::Colcon>::SharedPtr pub; //  인클루드한 것으로 타입 지정
   public:
    publisher();
    void publish_data();
    

};
class subscriber : public rclcpp::Node //서브스크라이버
{
    rclcpp::Subscription<custom_interfaces::msg::Colcon>::SharedPtr sub; //  인클루드한 것으로 타입 지정
    
   public:
    subscriber();
    void callback(const custom_interfaces::msg::Colcon::SharedPtr msg);//메시지를 받았을 때 호출할 콜백함수
};
