#include "for_control.hpp"
int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<controlling>());
  rclcpp::shutdown();
  return 0;
}