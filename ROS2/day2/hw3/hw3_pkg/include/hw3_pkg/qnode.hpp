/**
 * @file /include/hw3_pkg/qnode.hpp
 *
 * @brief Communications central!
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef hw3_pkg_QNODE_HPP_
#define hw3_pkg_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/
#ifndef Q_MOC_RUN
#include <rclcpp/rclcpp.hpp> 
#include <std_msgs/msg/string.hpp>  //스트링 타입 사용. 메시지 보내는 노드랑 받는 노드 사이의 통신할 때의 타입으로
#include <QObject>                  //publisher 클래스랑 subscriber_node 클래스 상속을 위해서
#include <QString>                  //QString으로 main_window의 slot 메서드에 전달하기 위해
#include <memory>
#endif
#include <QThread>
namespace Ui { class MainWindow; }
/*****************************************************************************
** Class
*****************************************************************************/
class publisher: public QObject, public rclcpp::Node{ //publisher 클래스 선언  
   Q_OBJECT    //버튼을 누르면 이 클래스의 connect되어 publish_message메서드가 slot메서드가 되어야 하기 때문
   rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub; 
   public:
   Ui::MainWindow* ui; //ui에 접근하여 버튼을 눌렀을 때 입력창의 문자열을 가져오기 위함
   publisher();
   public slots: //slots설정 위해 QObject상속 받음
   void publish_message(); //publish하는 메서드. ui->text로 입력창에 적힌 것 읽음
};
class subscribe_node: public QObject, public rclcpp::Node{
  Q_OBJECT //이거 써야 함
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub;     
  void topic_callback(const std_msgs::msg::String::SharedPtr msg); //메시지 받았을 때의 콜백 함수, 여기서 signal_func emit하여 강제로 시그널 발생시킴
  signals:
  void signal_func(QString str); //signals 설정하기 위해 QObject상속받음
  

  public:
  subscribe_node();
};
class QNode : public QThread
{
  Q_OBJECT
public:
  QNode();
  ~QNode();
  std::shared_ptr<subscribe_node> sub_ptr; 
  std::shared_ptr<publisher> pub_ptr;  //main_window에서 publish_message에 접근하기 위해 다리 역할을 하기 위해 선언
protected:
  void run();

private:
   
Q_SIGNALS:
  void rosShutDown();
};

#endif /* hw3_pkg_QNODE_HPP_ */
