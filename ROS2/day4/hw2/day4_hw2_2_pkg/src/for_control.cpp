#include "for_control.hpp"
#include <tf2/LinearMath/Quaternion.h>
#include <chrono>
#include <cmath>
using namespace std::chrono_literals;
controlling:: controlling():Node("control_node"){ //노드명 설정
    sub_ptr =this->create_subscription<geometry_msgs::msg::Twist>(
        "cmd_vel", 10, std::bind(&controlling::msg_callback, this, std::placeholders::_1)); //토픽명 설정 및 콜백메서드 바인딩
    tf_broadcaster = std::make_shared<tf2_ros::TransformBroadcaster>(this); //tf_broadcaster로 보낼 때 보낼 메시지를 타입으로 생성
    timer_= this->create_wall_timer(0.01s, std::bind(&controlling::timer_callback, this)); //0.01초마다 호출되도록 설정
}  
void controlling::msg_callback(const geometry_msgs::msg::Twist::SharedPtr msg){
    linear_v=msg->linear.x;  //msg받으면 callback메서드가 끝나면 내용이 소멸되므로 이를 멤버로 저장
    angular_v = msg-> angular.z; //timer_callback에서 이를 처리해야 하므로
}
void controlling::timer_callback(){
    double interval = 0.01;           //시간 간격은 당연히 0.01초
    x+= interval* linear_v*cos(angle); //선속도 하나만으로 x, y를 알 수 없기에 이를 시간 간격으로 그 때마다 거리를 누적
    y+= interval* linear_v*sin(angle); //선속도를 x성분, y성분으로 나눠서 각각 시간을 곱하여 0.01초에 평균속도 곱하여 대략적인 거리 계산
    angle+=interval*angular_v;  //각속도는 z축에 대해서만 보면 되기에 각속도에 시간을 곱해서 각도를 누적시킴

    rclcpp::Time now = this->get_clock()->now(); //메시지를 보낼 때 필요한 요소들을 대입시키기 위해 시간 가져옴
    geometry_msgs::msg::TransformStamped t; //메시지 타입 

    //t라는 메시지 보낼 때 충족시켜야 할 것인 header, child_frame, transform 초기화하는 부분
    t.header.stamp = now; 
    t.header.frame_id = "map"; //부모 프레임, map 그리고 map의 자식 프레임인 odom 그리고 baselink순으로 감 
    t.child_frame_id = "odom"; //과제에서는 map과 odom 간의 관계만 보기에 이와 같이 설정함

    t.transform.translation.x = x; //계산했었던 누적된 x좌표 대입
    t.transform.translation.y = y; //y좌표 대입
    t.transform.translation.z = 0.0;

    tf2::Quaternion q;//오일러 각도 변환을 쓸 수도 있지만 짐벌락 문제를 없애고자 쿼터니안 변환 라이브러리 사용
    q.setRPY(0, 0, angle);  //roll, pitch, yaw 중 yaw에 해당되는 3번째 매개변수에 누적된 각도값 넣음
    t.transform.rotation.x = q.x(); 
    t.transform.rotation.y = q.y();
    t.transform.rotation.z = q.z();  //x, y, z는 허수로 표현되는 것으로 알고 있음
    t.transform.rotation.w = q.w(); //각도값
    
    tf_broadcaster->sendTransform(t); //이 메서드를 통해 메시지 보냄
}