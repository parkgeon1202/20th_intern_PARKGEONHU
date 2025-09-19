/**
 * @file /include/day1_hw2_pkg/qnode.hpp
 *
 * @brief Communications central!
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef day1_hw2_pkg_QNODE_HPP_
#define day1_hw2_pkg_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/
#ifndef Q_MOC_RUN
#include <rclcpp/rclcpp.hpp>
#endif
#include <QThread>

#include <arpa/inet.h>   // htons, ntohs, inet_addr 등 IP 주소 변환
#include <sys/socket.h>  // socket(), sendto(), recvfrom() 등 소켓 함수
#include <netinet/in.h>  // sockaddr_in 구조체 정의
#include <unistd.h>      // close() 함수

/*****************************************************************************
** Class
*****************************************************************************/
class QNode : public QThread
{
  Q_OBJECT
public:
  QNode();
  ~QNode();

protected:
  void run();

private:
  std::shared_ptr<rclcpp::Node> node;

Q_SIGNALS:
  void rosShutDown();
};

#endif /* day1_hw2_pkg_QNODE_HPP_ */
