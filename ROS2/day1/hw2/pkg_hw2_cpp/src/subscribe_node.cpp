#include "pkg_hw2.hpp"

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    // 여기서 퍼블리셔 대신 서브스크라이버 노드를 실행
    auto node = std::make_shared<subscribe_node>();
    rclcpp::spin(node); //spin하여 계속 대기하도록 함
    rclcpp::shutdown();

    return 0;
}
