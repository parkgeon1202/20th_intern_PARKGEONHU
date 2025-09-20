#include "../include/hw4_pkg/qnode.hpp"
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<publisher>(); //퍼블리셔 노드 생성
    node->publish_message(); //spin만 하면 publish_message가 호출될 여지가 없고, 무한 반복하는 메서드이니 spin()보다 윗줄에서 호출
    rclcpp::spin(node); 
    rclcpp::shutdown();
    return 0;
}