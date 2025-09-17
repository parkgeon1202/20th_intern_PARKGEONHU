/**
 * @file /src/main_window.cpp
 *
 * @brief Implementation for the qt gui.
 *
 * @date August 2024
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include "../include/hw2_pkg/main_window.hpp"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QLineEdit>
#include <QString>
MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow){
  ui->setupUi(this);
 


  qnode = new QNode();
  qnode->pub_ptr->ui = ui; //publisher 클래스의 ui포인터에 mainwindow의 ui포인터를 넣어줘서 publisher내부에서 ui접근 가능하게 함

  QObject::connect(qnode, SIGNAL(rosShutDown()), this, SLOT(close()));
 
}

void MainWindow::closeEvent(QCloseEvent* event)
{
  QMainWindow::closeEvent(event);
}

MainWindow::~MainWindow()
{
  delete ui;
  delete qnode;

}
//각 번호에 대한 출력을 다르게 함 qnode의 publisher클래스의 publish_message함수를 호출
void MainWindow::on_drawSquare_clicked(){
  qnode-> pub_ptr->publish_message(1);
}
void MainWindow::on_drawTriangle_clicked(){
  qnode-> pub_ptr->publish_message(2);
}
void MainWindow::on_drawCircle_clicked(){
  qnode-> pub_ptr->publish_message(3);
}
void MainWindow::on_Delete_clicked(){ 
  qnode-> pub_ptr->publish_message(4);
}
// subscribe_node::subscribe_node(Ui::MainWindow* ui):Node("subscribe_node"), ui(ui){
//     sub = this->create_subscription<geometry_msgs::msg::Twist>("turtle1/cmd_vel",10,std::bind(&subscribe_node::topic_callback,this,std::placeholders::_1));
// }
// void subscribe_node:: topic_callback( const geometry_msgs::msg::Twist::SharedPtr msg){
//     ui->lineEdit-> setText("linear: "+QString::number(msg->linear.x) + "," + "angular: "+QString::number(msg->angular.z));
// }
