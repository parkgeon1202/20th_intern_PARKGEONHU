cmake_minimum_required(VERSION 3.5)
project(day4_hw2_2_pkg)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)


include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include/day4_hw2_2_pkg
)


add_executable(for_control src/for_control.cpp src/main.cpp)
ament_target_dependencies(for_control
  rclcpp
  geometry_msgs
  tf2
  tf2_ros
)


install(TARGETS
  for_control
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY include
  DESTINATION include
)

ament_package()
