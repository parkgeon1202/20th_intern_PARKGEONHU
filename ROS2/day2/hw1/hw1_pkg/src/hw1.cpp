#include "hw1.hpp"
#include <iostream>

publisher::publisher() : Node("publisher") //노드명 설정
{
    pub = this->create_publisher<custom_interfaces::msg::Colcon>("topic", 10); //퍼블리시 포인터 생성, 토픽명 설정
}
void publisher:: publish_data(){ //데이터 발행 함수
    int num=0;
    custom_interfaces::msg::Colcon data; 
    RCLCPP_INFO(this->get_logger(), "10개의 정수를 입력하세요: "); //콘솔에 출력
    for(int i=0; i< 10; i++){
    std::cin>> num; 
    if(!std::cin){ //예외 처리함
        std::cout<<"다시 입력하세요"<<std::endl;
        std::cin.clear();   
        std::cin.ignore(1000, '\n'); 
        i--;    //잘못 입력받았으니 다시 입력받도록 입력받는 횟수 처리
        continue; 
    }
     
    int integer = num;
    
    data.data.push_back(integer); // msg파일에서 []를 사용할 경우 이는 cpp파일로 만들어질 때 벡터로 변환되기에 push_back사용
    //msg파일에서 data라고 이름을 지었기에 data라는 벡터 멤버가 있는 것
    }
    pub->publish(data);

}
void subscriber::callback(const custom_interfaces::msg::Colcon::SharedPtr msg){ // 메시지를 받았을 때 호출할 콜백함수
   
    RCLCPP_INFO(this->get_logger(), "받은 데이터: ");
    for(auto i : msg->data){
       
    RCLCPP_INFO(this->get_logger(), "%d ", (i)); //받은 모든 데이터를 잘 받았음을 확인하기 위해 각각 출력함
    }
}
subscriber::subscriber() : Node("subscriber") //노드명 설정
{
    sub = this->create_subscription<custom_interfaces::msg::Colcon>(
        "topic", 10, std::bind(&subscriber::callback, this, std::placeholders::_1)); //서브스크립션 포인터 생성, 토픽명 설정, 콜백함수 바인딩
}