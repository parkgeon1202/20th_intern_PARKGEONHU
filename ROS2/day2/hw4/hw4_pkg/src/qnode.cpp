/**
 * @file /src/qnode.cpp
 *
 * @brief Ros communication central!
 *
 * @date August 2024
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include "../include/hw4_pkg/qnode.hpp"

QNode::QNode()
{
  int argc = 0;
  char** argv = NULL;
  rclcpp::init(argc, argv);
  sub_ptr = std::make_shared<subscribe_node>();  //subscribe_node 객체 생성
  this->start();
}

QNode::~QNode()
{
  if (rclcpp::ok())
  {
    rclcpp::shutdown();
  }
}

void QNode::run()
{
  rclcpp::WallRate loop_rate(20);
  while (rclcpp::ok())
  {
    rclcpp::spin(sub_ptr); //처음에는 sub_ptr을 connect때문에 subscribe_node*로 하려 했지만 spin에 넣을 수 없어 shaged_ptr로 함
    loop_rate.sleep();
  }
  rclcpp::shutdown();
  Q_EMIT rosShutDown();
}
publisher::publisher():Node("publish_node"){ // publisher 클래스 생성자, 노드 이름 설정
    pub = this->create_publisher<custom_interfaces::msg::RobotArm>("hw4_pkg",10); //토픽 이름 설정
}

void publisher::publish_message(){
    int part=0;
    int angle=0;
    while(1){  
     RCLCPP_INFO(this->get_logger(),"움직일 부분(하단: 1, 중간부: 2, 상단: 3), 움직일 각도"); //입력해야 할 것 터미널에서 알려주기
     std::cin>>part; //터미널로부터 값 입력 받기 
     //예외처리
     if(!std::cin|| part<1 || part>3){ //1,2,3 정수만 받음
         RCLCPP_INFO(this->get_logger(),"잘못된 입력입니다. 처음부터 다시 입력하세요");
         std::cin.clear();
         std::cin.ignore(1000,'\n');
         continue;
     }
     std::cin>>angle;
     if(!std::cin|| angle<0 || angle>360){ //각도는 0~360
         RCLCPP_INFO(this->get_logger(),"잘못된 입력입니다. 처음부터 다시 입력하세요");
         std::cin.clear();
         std::cin.ignore(1000,'\n');
         continue;
     }
      custom_interfaces::msg::RobotArm temp; //temp객체 생성해서 아래에서 멤버 모두 값 초기화해줌
      temp.flag=part;
      temp.angle = angle;
      pub->publish(temp);
      // std::this_thread::sleep_for(std::chrono::seconds(3));
   }
}
subscribe_node::subscribe_node():Node("subscribe_node"){
 
    sub = this->create_subscription<custom_interfaces::msg::RobotArm>("hw4_pkg",10,std::bind(&subscribe_node::topic_callback,this,std::placeholders::_1));
}
void subscribe_node:: topic_callback( const custom_interfaces::msg::RobotArm::SharedPtr msg){
   emit signal_func(msg->flag, msg->angle); //callback에서 emit함 메시지는 콜백함수가 끝나면 사라지기 때문에 시그널을 발생시켜서 connect로 MainWindow slot함수에게 정보 넘기도록 설계함

}