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

#include "../include/hw4_pkg/main_window.hpp"
#include <QSpinBox>
#include <QVBoxLayout>
#include "ui_mainwindow.h"
#include "hw4_pkg/arm.h"
MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  
  ui->spinBox->setRange(0, 360);             //최대 두자리 수여서 360까지 값을 받을 수 있도록 설정
  ui->spinBox_2->setRange(0, 360);
  ui->spinBox_3->setRange(0, 360);
  armView = new ArmView(this);               //동적할당하여 객체 생성하여 이 객체로 팔 조절
    auto *layout = new QVBoxLayout(ui->armViewHost); //로봇팔을 위젯 위에 그리기 위한 설정
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(armView);
  qnode = new QNode();
  connect(qnode->sub_ptr.get(), &subscribe_node::init_func, this, &MainWindow::get_init);
  connect(qnode->sub_ptr.get(), &subscribe_node::signal_func, this, &MainWindow::control_arm); //ros부문인 subscribe_node의 받은 메시지 정보를 qt 부문인 MainWindow로 넘기는 방법
  
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
//spin Box에 대한 슬롯 함수 정의 입력 받은 각도 값으로 그만큼 회전
void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
    armView->setMiddleAngle(arg1);
}


void MainWindow::on_spinBox_valueChanged(int arg1)
{
    armView->setBottomAngle(arg1);
}


void MainWindow::on_spinBox_3_valueChanged(int arg1)
{
    armView->setUpperAngle(arg1);
}
//setValue로 위 slot 메서드들을 호출하는 시그널 발생시킴
void MainWindow::control_arm(int flag, int angle){
  if(flag==1){
    ui->spinBox->setValue(angle);
  }
  else if(flag==2){
    ui->spinBox_2->setValue(angle);
  }
  else if(flag==3){
    ui->spinBox_3->setValue(angle);
  }
}
void MainWindow::get_init(double L1,double L2,double L3,double a0,double a1,double a2){
  armView->L1= L1;
  armView->L2= L2;
  armView->L3= L3;
  armView->a0= a0;
  armView->a1= a1;
  armView->a2= a2;  
}