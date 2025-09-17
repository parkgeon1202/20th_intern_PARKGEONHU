#include "day4_hw1_pkg/lifecycle_sub.hpp"
int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    std::shared_ptr<sub_cycle> minimal_subscriber = std::make_shared<sub_cycle>();  
    rclcpp::spin(minimal_subscriber->get_node_base_interface()); //핵심 인터페이스만 꺼내서 타입 불일치 해결
    // rclcpp::spin(std::make_shared<sub_cycle>());
    rclcpp::shutdown();
    return 0;
}