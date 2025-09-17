cmake_minimum_required(VERSION 3.8)
project(day4_hw1_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# --- deps ---
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rclcpp_lifecycle REQUIRED)  # ★ 라이프사이클 헤더/링크

# 헤더 경로
include_directories(${PROJECT_SOURCE_DIR}/include)

# --- 일반 퍼블리셔/서브스크라이버 (lifecycle 헤더 사용하지 않음) ---
add_executable(publisher_node src/publisher.cpp src/lifecycle_pub.cpp)
ament_target_dependencies(publisher_node rclcpp rclcpp_lifecycle std_msgs)

add_executable(subscriber_node src/subscriber.cpp src/lifecycle_sub.cpp)
ament_target_dependencies(subscriber_node rclcpp rclcpp_lifecycle std_msgs)


# 설치
install(TARGETS
  publisher_node
  subscriber_node

  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
