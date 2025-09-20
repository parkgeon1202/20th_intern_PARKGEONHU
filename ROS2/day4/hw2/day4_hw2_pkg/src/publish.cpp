#include "control.hpp"
int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<joy_subscribe>());
  rclcpp::shutdown();
  return 0;
}