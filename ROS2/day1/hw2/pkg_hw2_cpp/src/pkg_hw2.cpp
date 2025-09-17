#include "pkg_hw2.hpp"
#include <chrono> 
using namespace std::chrono_literals; //chrono_literals의 부분을 쉽게 사용하기 위해 선언

      MyCppNode:: MyCppNode():Node("publish_node"){
        RCLCPP_INFO(this->get_logger(), "Hello, ROS 2 C++ Node!"); //처음에 한번만 출력
        //각자 토픽 이름 생성하고 퍼블리셔 생성
        mycpp_publisher_= this->create_publisher<std_msgs::msg::String>("topicname", 10);
        mycpp_publisher_int= this->create_publisher<std_msgs::msg::Int32>("int_topic", 10);
        mycpp_publisher_float= this->create_publisher<std_msgs::msg::Float32>("float_topic", 10);
        timer_= this->create_wall_timer(1s, std::bind(&MyCppNode::timer_callback, this)); //타이머 생성, 강의자료 예제 코드 사용
      }

      
      void MyCppNode:: timer_callback(){ //1초마다 호출되는 콜백함수
         //각기 메시지 담을 그릇 생성
        auto msg = std_msgs::msg::String();
        auto num = std_msgs::msg::Int32();
        auto fl= std_msgs::msg::Float32();
        //메시지 담기
        msg.data= "Hello World: "+ std::to_string(count_++);
        num.data = 3456+count_;
        fl.data = 3.4567+count_;
        //터미널 출력
        RCLCPP_INFO(this->get_logger(), "Published message: '%s', int: '%d', float: '%f'", msg.data.c_str(), num.data, fl.data);
        //각각 퍼블리시
        mycpp_publisher_ -> publish(msg);
        mycpp_publisher_int->publish(num);
        mycpp_publisher_float->publish(fl);
      }
      

      
   






     //각각의 받는 메서드 정의: 터미널 출력함. 메시지를 받았고 이를 출력하는 것, SharedPtr로 전달 받은 객체 가리킴
     void subscribe_node:: topic_callback_str(const std_msgs::msg::String::SharedPtr msg){
        
        RCLCPP_INFO(this->get_logger(), "Received message: '%s'", msg->data.c_str());
     }
     void subscribe_node:: topic_callback_int( const std_msgs::msg::Int32::SharedPtr num){
        
        RCLCPP_INFO(this->get_logger(), "Received message: '%d'",  num->data);
     }
     void subscribe_node:: topic_callback_float( const std_msgs::msg::Float32::SharedPtr fl){
        
        RCLCPP_INFO(this->get_logger(), "Received message: '%f'", fl->data);
     }
     //노드 이름을 subscribe_node로 지정, 각자 토픽 이름 생성하고 서브스크라이버 포인터 생성
     subscribe_node:: subscribe_node():Node("subscribe_node"){
         mycpp_subscriber_= this->create_subscription<std_msgs::msg::String>("topicname", 10, std::bind(&subscribe_node::topic_callback_str, this, std::placeholders::_1));
         mycpp_subscriber_int =  this->create_subscription<std_msgs::msg::Int32>("int_topic", 10, std::bind(&subscribe_node::topic_callback_int, this, std::placeholders::_1));
         mycpp_subscriber_float =  this->create_subscription<std_msgs::msg::Float32>("float_topic", 10, std::bind(&subscribe_node::topic_callback_float, this, std::placeholders::_1));
      }

