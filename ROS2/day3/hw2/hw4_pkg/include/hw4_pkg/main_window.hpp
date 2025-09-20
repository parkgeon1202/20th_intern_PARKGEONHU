/**
 * @file /include/hw4_pkg/main_window.hpp
 *
 * @brief Qt based gui for %(package)s.
 *
 * @date August 2024
 **/

#ifndef hw4_pkg_MAIN_WINDOW_H
#define hw4_pkg_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QMainWindow>
#include "qnode.hpp"


/*****************************************************************************
** Interface [MainWindow]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */
class ArmView;
class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();
  QNode* qnode;

private:
  Ui::MainWindow* ui;
  ArmView* armView;  //armview 포인터 생성
  void closeEvent(QCloseEvent* event);
private slots:
  void get_init(double L1,double L2,double L3,double a0,double a1,double a2);
  void control_arm(int flag, int angle); //flag, angle 값을 받아 시그널을 발생시켜서 아래의 slot함수들을 호출하는 역할.
  void on_spinBox_valueChanged(int v);
  void on_spinBox_2_valueChanged(int v);
  void on_spinBox_3_valueChanged(int v);
};

#endif  // hw4_pkg_MAIN_WINDOW_H
