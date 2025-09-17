#include "pkg_hw2.hpp"
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MyCppNode>(); //퍼블리셔 노드 생성
    rclcpp::spin(node); //spin하여 계속 프로그램이 돌아가도록 함
    rclcpp::shutdown();
    return 0;
}
