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

#include "../include/hw3_pkg/qnode.hpp"
#include "ui_mainwindow.h"

QNode::QNode()
{
  int argc = 0;
  char** argv = NULL;
  rclcpp::init(argc, argv);
  sub_ptr = std::make_shared<subscribe_node>();  //subscribe_node 객체 생성
  pub_ptr = std::make_shared<publisher>();       //publisher 객체 생성
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
    rclcpp::spin_some(sub_ptr);  //여기서 subscribe_node가 대기함
    loop_rate.sleep();
  }
  rclcpp::shutdown();
  Q_EMIT rosShutDown();
}
publisher::publisher():Node("publish_node"){ // publisher 클래스 생성자, 노드 이름 설정
    pub = this->create_publisher<std_msgs::msg::String>("hw3_pkg",10); //토픽 이름 설정
}
void publisher::publish_message(){
    
      std_msgs::msg::String str;      
      QString s = ui->input->text();   //ui에서 받아와서 저장
      str.data = s.toStdString();      //문자열로 변환해서 보낼 변수에 저장
      pub->publish(str);             
}
subscribe_node::subscribe_node():Node("subscribe_node"){
 
    sub = this->create_subscription<std_msgs::msg::String>("hw3_pkg",10,std::bind(&subscribe_node::topic_callback,this,std::placeholders::_1));
}
void subscribe_node:: topic_callback( const std_msgs::msg::String::SharedPtr msg){
   emit signal_func(QString::fromStdString(msg->data)); //callback에서 emit함 메시지는 콜백함수가 끝나면 사라지기 때문에 시그널을 발생시켜서 connect로 MainWindow slot함수에게 정보 넘기도록 설계함

}