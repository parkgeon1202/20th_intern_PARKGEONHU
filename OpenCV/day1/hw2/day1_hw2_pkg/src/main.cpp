#include <QApplication>
#include <iostream>

#include "../include/day1_hw2_pkg/main_window.hpp"

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}
