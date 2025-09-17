#include <QApplication>
#include <iostream>

#include "../include/hw4_pkg/main_window.hpp"

int main(int argc, char* argv[])
{
  rclcpp::init(argc, argv);
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}
