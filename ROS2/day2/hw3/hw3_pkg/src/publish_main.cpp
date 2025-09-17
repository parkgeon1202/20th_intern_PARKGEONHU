#include "../include/hw3_pkg/qnode.hpp"
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<publisher>(); //퍼블리셔 노드 생성
    rclcpp::spin(node);  //이번에는 버튼 누르는 이벤트가 생겨야 publish_message호출하도록 되어야 하니 spin()으로 계속 대기하도록 함
    rclcpp::shutdown();
    return 0;
}