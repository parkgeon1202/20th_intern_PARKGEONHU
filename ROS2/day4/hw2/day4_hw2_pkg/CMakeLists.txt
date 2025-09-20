cmake_minimum_required(VERSION 3.5)
project(day4_hw2_pkg)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)


include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include/day4_hw2_pkg
)


add_executable(control src/control.cpp src/publish.cpp)
ament_target_dependencies(control
  rclcpp
  sensor_msgs
  geometry_msgs
)


install(TARGETS
  control
  DESTINATION lib/${PROJECT_NAME}
)


install(DIRECTORY launch config include
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
