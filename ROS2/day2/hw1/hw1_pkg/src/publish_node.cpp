#include "hw1.hpp"
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<publisher>(); 
    node->publish_data(); //spin만 하다보면 해당 publish_data가 호출되지 않을 수 있기에 spin전에 호출하여 구현되도록 함
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
