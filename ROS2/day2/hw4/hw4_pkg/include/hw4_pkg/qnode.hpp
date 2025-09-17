/**
 * @file /include/hw4_pkg/qnode.hpp
 *
 * @brief Communications central!
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef hw4_pkg_QNODE_HPP_
#define hw4_pkg_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/
#ifndef Q_MOC_RUN
#include <rclcpp/rclcpp.hpp>
#include "custom_interfaces/msg/robot_arm.hpp" //custom_interfaces 활용 멤버: int32 flag, int32 angle
#include <memory>
#endif
#include<QObject> //subscribe_node에서 QObject 상속받기 위해 
#include <QThread>

/*****************************************************************************
** Class
*****************************************************************************/
namespace Ui{class MainWindow;}
class publisher: public rclcpp::Node{ //publisher 클래스 선언  

   rclcpp::Publisher<custom_interfaces::msg::RobotArm>::SharedPtr pub;
   
   
   public:
   
   publisher();
   void publish_message(); //값을 입력받아 publish하는 메서드
};
class subscribe_node: public QObject, public rclcpp::Node{
  Q_OBJECT //이거 써야 함
  rclcpp::Subscription<custom_interfaces::msg::RobotArm>::SharedPtr sub;     
  void topic_callback(const custom_interfaces::msg::RobotArm::SharedPtr msg); //메시지 받았을 때의 콜백 함수, 여기서 signal_func emit하여 강제로 시그널 발생시킴
  signals:
  void signal_func(int flag, int angle); //signals 설정하기 위해 QObject상속받음
  

  public:
  subscribe_node();
};
class QNode : public QThread
{
  Q_OBJECT
public:
  QNode();
  ~QNode();
  //std::shared_ptr<publisher> pub_ptr;
  std::shared_ptr<subscribe_node> sub_ptr; // main_window의 qnode포인터로 ros 부문인 subscribe_node와 연결짓기 위해 선언
protected:
  void run();

private:
 

Q_SIGNALS:
  void rosShutDown();
};

#endif /* hw4_pkg_QNODE_HPP_ */
