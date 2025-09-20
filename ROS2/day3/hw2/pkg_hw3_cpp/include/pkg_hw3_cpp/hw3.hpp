#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp> //토픽 타입을 사용하기 위해 헤더 선언
#include <turtlesim/srv/set_pen.hpp>  //색, 두께를 바꿀 수 있는 타입 사용을 위해 선언
#include <std_srvs/srv/empty.hpp> //터틀의 화면을 지우기 위해 비워줄 수 있는 타입 선언
class publisher: public rclcpp::Node{
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr pub; //퍼블리셔 객체 선언
    rclcpp::Client<turtlesim::srv::SetPen>::SharedPtr set_pen; //서비스 클라이언트 객체 선언 
    public:
    publisher(); 
    void publish_message(); //퍼블리셔 함수 선언
    
};
