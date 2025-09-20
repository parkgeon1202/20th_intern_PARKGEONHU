cmake_minimum_required(VERSION 3.5)

project(hw1_package LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt 자동 생성기
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)

# 실제 파일들 (경로/이름 그대로)
set(PROJECT_SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/arm.cpp
    include/mainwindow.h
    include/arm.h
    ui/mainwindow.ui
)

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
)

# 헤더가 include/ 밑에 있으므로 include 경로 추가(선택이지만 안전)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)
