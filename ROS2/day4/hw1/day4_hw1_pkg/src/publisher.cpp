#include "day4_hw1_pkg/lifecycle_pub.hpp"

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    std::shared_ptr<pub_cycle> minimal_publisher = std::make_shared<pub_cycle>();
    rclcpp::spin(minimal_publisher->get_node_base_interface());//핵심 인터페이스만 꺼내서 타입 불일치 해결
    rclcpp::shutdown();
    return 0;
}