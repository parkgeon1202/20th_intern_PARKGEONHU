#include "hw3.hpp"
int main(int argc, char * argv[]){
    rclcpp::init(argc,argv);
    auto node = std::make_shared<publisher>();     //노드 객체 생성
    node->publish_message(); //퍼블리셔 함수 실행 while문으로 무한반복하기 때문에 spin이 필요 없음
    rclcpp::shutdown();
    return 0;
}