cmake_minimum_required(VERSION 3.5)
project(hw3_pkg)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt 자동 처리 대신 수동 래퍼 사용 (현재 구조 유지)
set(CMAKE_AUTOUIC OFF)
set(CMAKE_AUTOMOC OFF)
set(CMAKE_AUTORCC ON)

# -------- Dependencies --------
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(Boost 1.71.0 REQUIRED COMPONENTS thread)
find_package(Qt5 REQUIRED COMPONENTS Widgets Core Gui Network)

# -------- Files --------
file(GLOB PRO_SOURCE_DIR    RELATIVE ${CMAKE_SOURCE_DIR} FOLLOW_SYMLINKS src/*.cpp)
file(GLOB PRO_UI_DIR        RELATIVE ${CMAKE_SOURCE_DIR} FOLLOW_SYMLINKS ui/*.ui)
file(GLOB PRO_INCLUDE_DIR   RELATIVE ${CMAKE_SOURCE_DIR} FOLLOW_SYMLINKS include/${PROJECT_NAME}/*.h include/${PROJECT_NAME}/*.hpp)
file(GLOB PRO_RESOURCE_DIR  RELATIVE ${CMAKE_SOURCE_DIR} FOLLOW_SYMLINKS resource/*.qrc)

# Qt wrap (moc/ui/qrc)
qt5_wrap_ui(QT_UI_HPP ${PRO_UI_DIR})
qt5_wrap_cpp(QT_MOC_HPP ${PRO_INCLUDE_DIR})
qt5_add_resources(QT_RESOURCE_CPP ${PRO_RESOURCE_DIR})

include_directories(
  include/
  ${CMAKE_CURRENT_BINARY_DIR}
)

# -------- publish_node --------
# publish_node는 publish_main.cpp + qnode.cpp + main_window.cpp 만 포함 (UI 구현 필요)
set(PUBLISH_SOURCES
  src/publish_main.cpp
  src/qnode.cpp
  src/main_window.cpp
)

add_executable(publish_node
  ${PUBLISH_SOURCES}
  ${PRO_INCLUDE_DIR}
  ${QT_MOC_HPP}
  ${QT_RESOURCE_CPP}
  ${QT_UI_HPP}
)

ament_target_dependencies(publish_node rclcpp std_msgs Boost)
target_link_libraries(publish_node Qt5::Widgets Qt5::Core Qt5::Gui Qt5::Network)

# -------- subscribe_node --------
# subscribe_node는 src/의 모든 cpp에서 publish_main.cpp만 제외
set(SUBSCRIBE_SOURCES ${PRO_SOURCE_DIR})
list(FILTER SUBSCRIBE_SOURCES EXCLUDE REGEX ".*/publish_main\\.cpp$")

add_executable(subscribe_node
  ${SUBSCRIBE_SOURCES}
  ${PRO_INCLUDE_DIR}
  ${QT_MOC_HPP}
  ${QT_RESOURCE_CPP}
  ${QT_UI_HPP}
)

ament_target_dependencies(subscribe_node rclcpp std_msgs Boost)
target_link_libraries(subscribe_node Qt5::Widgets Qt5::Core Qt5::Gui Qt5::Network)

# -------- Install --------
install(TARGETS publish_node DESTINATION lib/${PROJECT_NAME})
install(TARGETS subscribe_node DESTINATION lib/${PROJECT_NAME})

# -------- Tests --------
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()