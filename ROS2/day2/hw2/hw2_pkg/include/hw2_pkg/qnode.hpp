/**
 * @file /include/hw2_pkg/qnode.hpp
 *
 * @brief Communications central!
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef hw2_pkg_QNODE_HPP_
#define hw2_pkg_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/
#ifndef Q_MOC_RUN
#include <rclcpp/rclcpp.hpp>
//3번 과제에서 인클루드 했던 대로 인클루드함
#include <geometry_msgs/msg/twist.hpp> 
#include <turtlesim/srv/set_pen.hpp>
#include <std_srvs/srv/empty.hpp>
#endif
#include <QThread>

namespace Ui { class MainWindow; }
/*****************************************************************************
** Class
*****************************************************************************/
class publisher: public rclcpp::Node{ //publisher 클래스 선언  
   //3번 과제에서 선언한 포인터 그대로 사용
   rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr pub;
   rclcpp::Client<turtlesim::srv::SetPen>::SharedPtr set_pen;
   
   public:
   Ui:: MainWindow* ui; //ui에 접근하기 위해 포인터 선언하고 publisher 내부에서 MainWindow 내부처럼 코드 작업 가능
   publisher();
   void publish_message(int flag); //버튼을 누르는 것으로 어떤 동작을 수행하게 publish할지 달라지기에 int형태로 flag를 받음
};

class QNode : public QThread
{
  Q_OBJECT
public:
  QNode();
  ~QNode();
  std::shared_ptr<publisher> pub_ptr;  //Qt쪽인 main_window와 ros간의 소통을 할 때 qnode의 클래스를 통해 소통을 하게 된다
                                      //그래서 main_window의 qnode포인터가 ros부분에 잘 명령할 수 있게 qnode클래스에 publisher클래스의 포인터를 멤버로 선언
protected:
  void run();

private:
 
  
Q_SIGNALS:
  void rosShutDown();
};

#endif /* hw2_pkg_QNODE_HPP_ */
