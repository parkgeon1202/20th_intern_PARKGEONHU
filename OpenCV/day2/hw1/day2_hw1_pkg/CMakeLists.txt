cmake_minimum_required(VERSION 3.5)
project(day2_hw1_pkg)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)


find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

find_package(OpenCV REQUIRED)


set(PROJECT_HEADERS
  include/day2_hw1_pkg/main_window.hpp
  include/day2_hw1_pkg/qnode.hpp
)

set(PROJECT_SOURCES
  src/main.cpp
  src/main_window.cpp
  src/qnode.cpp
)

set(PROJECT_UIS
  ui/mainwindow.ui
)

set(PROJECT_RESOURCES
  resources/images.qrc
)


add_executable(${PROJECT_NAME}
  ${PROJECT_SOURCES}
  ${PROJECT_HEADERS}
  ${PROJECT_UIS}
  ${PROJECT_RESOURCES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${OpenCV_INCLUDE_DIRS}
)

ament_target_dependencies(${PROJECT_NAME}
  rclcpp
)

target_link_libraries(${PROJECT_NAME}
  Qt${QT_VERSION_MAJOR}::Widgets
  Qt${QT_VERSION_MAJOR}::Network
  ${OpenCV_LIBS}
)

install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)


install(DIRECTORY resources/images
  DESTINATION share/${PROJECT_NAME}/resources
)

ament_package()
