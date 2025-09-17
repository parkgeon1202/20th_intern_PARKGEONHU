/**
 * @file /include/hw3_pkg/main_window.hpp
 *
 * @brief Qt based gui for %(package)s.
 *
 * @date August 2024
 **/

#ifndef hw3_pkg_MAIN_WINDOW_H
#define hw3_pkg_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/
namespace Ui{class MainWindow;}
#include <QMainWindow>
#include "qnode.hpp"


/*****************************************************************************
** Interface [MainWindow]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */
class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();
  QNode* qnode;
  friend class publisher; //publish_message에서 같은 윈도우 창을 가리켜서 입력창에 있는 문자열 작업을 쉽게 하기 위함

private:
  Ui::MainWindow* ui;
  void closeEvent(QCloseEvent* event);
private slots:
  void set_text(QString str); //subscribe_node의 시그널을 받으면 호출되는 slot 메서드. 이것으로 출력창에 받은 문자열을 출력함
};

#endif  // hw3_pkg_MAIN_WINDOW_H
