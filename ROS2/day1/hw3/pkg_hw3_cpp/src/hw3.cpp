#include "hw3.hpp"
#include <iostream>
#include <chrono>
publisher::publisher():Node("publish_node"){ //노드명 설정
    pub = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel",10); //해당 토픽명으로 퍼블리셔 생성
    set_pen = this->create_client<turtlesim::srv::SetPen>("turtle1/set_pen"); //서비스 클라이언트 생성

}
void publisher::publish_message(){
    char ch=0;
    while(1){  
     RCLCPP_INFO(this->get_logger(),"W: 정사각형, A: 정삼각형, S: 원, D: 삭제");
     std::cin>>ch; //터미널로부터 값 입력 받기 
     //예외처리
     if(!std::cin||(ch!='W'&& ch!= 'w'&&ch!='A'&& ch!='a'&&ch!='S'&& ch!='s'&&ch!='D'&& ch!='d')){
         RCLCPP_INFO(this->get_logger(),"잘못된 입력입니다.");
         std::cin.clear();
         std::cin.ignore(1000,'\n');
         continue;
     }
     if(ch == 'W'|| ch=='w'){ //w 입력시 정사각형 그림
        auto req = std::make_shared<turtlesim::srv::SetPen::Request>(); //펜 설정을 바꾸기 위해서는 Request사용해야 함
        req->r = 255; //빨간색으로 설정
        req->g = 0;
        req->b = 0;
        req->width = 3; //두께 설정
        set_pen->async_send_request(req); //서비스 요청
        geometry_msgs::msg::Twist temp; //메시지 타입 객체 생성
        for(int i=0;i<4;i++){ 
        temp.linear.x=2.0;
        temp.angular.z=0.0;
        pub-> publish(temp); 
        std::this_thread::sleep_for(std::chrono::seconds(3));
        temp.linear.x=0.0;
        temp.angular.z=1.57;
        pub-> publish(temp);
        std::this_thread::sleep_for(std::chrono::seconds(3));
     }
    }
     else if(ch== 'A'||ch=='a'){ // 세모 그림
        auto req = std::make_shared<turtlesim::srv::SetPen::Request>();
        req->r = 0;
        req->g = 255; //초록색으로 설정
        req->b = 0;
        req->width = 7; //두께 설정
        set_pen->async_send_request(req);
        geometry_msgs::msg::Twist temp;
        for(int i=0;i<3;i++){
        temp.linear.x=2.0;
        temp.angular.z=0.0;
        pub-> publish(temp);
        std::this_thread::sleep_for(std::chrono::seconds(3));
        temp.linear.x=0.0;
        temp.angular.z=2.09;
        pub-> publish(temp);
        std::this_thread::sleep_for(std::chrono::seconds(3));
     }
    }
     else if(ch== 'S'||ch=='s'){//원 그림
        auto req = std::make_shared<turtlesim::srv::SetPen::Request>();
        req->r = 0;
        req->g = 0;
        req->b = 255; //파란색으로 설정
        req->width = 10; //두께 설정
        set_pen->async_send_request(req);
        geometry_msgs::msg::Twist temp;
        for(int i=0; i<4; i++){
        temp.linear.x=2.0;
        temp.angular.z=1.8;
        pub-> publish(temp);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        
      }
     else if(ch== 'D'||ch=='d'){ //지금까지 그린 것 삭제
        rclcpp::Client<std_srvs::srv::Empty>::SharedPtr empty_ptr;
        empty_ptr = this->create_client<std_srvs::srv::Empty>("/clear"); //서비스 이름
        auto request = std::make_shared<std_srvs::srv::Empty::Request>(); //서비스 요청하기 위해 Request객체 생성
        empty_ptr->async_send_request(request);
     }
    
    }
}
