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

#include "../include/hw3_pkg/main_window.hpp" 
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);  
  qnode = new QNode();
  qnode->pub_ptr->ui = ui; //publisher객체의 ui변수에 MainWindow의 ui변수를 대입하여 같은 윈도우 창을 가리키도록 함
  connect(ui->publish, &QPushButton::clicked, qnode->pub_ptr.get(), &publisher::publish_message); //버튼이 눌렸을 때 publish로 이어지도록 하는 설정
  connect(qnode->sub_ptr.get(), &subscribe_node::signal_func, this, &MainWindow::set_text); //그리고 콜백함수에서 시그널을 발생되면 바로 문자열 출력하는 메서드와 연결되어 출력창에 문자열을 출력하도록 함
  QObject::connect(qnode, SIGNAL(rosShutDown()), this, SLOT(close()));
}

void MainWindow::closeEvent(QCloseEvent* event)
{
  QMainWindow::closeEvent(event);
}

MainWindow::~MainWindow()
{
  delete ui;
}
void MainWindow::set_text(QString str){
  ui->output->setText(str); //문자열 출력하는 부분
}
