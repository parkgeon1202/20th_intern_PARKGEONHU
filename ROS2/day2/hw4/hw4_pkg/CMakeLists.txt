cmake_minimum_required(VERSION 3.5)
project(hw4_pkg)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)


find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(custom_interfaces REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Widgets Core Gui)


set(UI_FILES
  ui/mainwindow.ui
)

set(RCC_FILES
  resources/images.qrc
)

set(GUI_HDRS
  include/${PROJECT_NAME}/arm.h
  include/${PROJECT_NAME}/main_window.hpp
)

set(COMMON_HDRS
  include/${PROJECT_NAME}/qnode.hpp
)

set(SRC_COMMON
  src/qnode.cpp
)

set(SRC_GUI
  src/main.cpp
  src/main_window.cpp
  src/arm.cpp
)

set(SRC_PUB
  src/publish_main.cpp
)


add_executable(subscribe_node
  ${SRC_COMMON}
  ${SRC_GUI}
  ${UI_FILES}
  ${RCC_FILES}
  ${GUI_HDRS}
  ${COMMON_HDRS}
)

target_include_directories(subscribe_node PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_BINARY_DIR}  
)

target_link_libraries(subscribe_node
  Qt5::Widgets Qt5::Core Qt5::Gui
)

ament_target_dependencies(subscribe_node
  rclcpp std_msgs custom_interfaces
)


add_executable(publish_node
  ${SRC_COMMON}
  ${SRC_PUB}
  ${COMMON_HDRS}            
)

target_include_directories(publish_node PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(publish_node
  Qt5::Core                  
)

ament_target_dependencies(publish_node
  rclcpp std_msgs custom_interfaces
)

install(TARGETS subscribe_node publish_node
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()