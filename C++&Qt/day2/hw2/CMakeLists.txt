cmake_minimum_required(VERSION 3.19)
project(hw2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt 자동 생성 설정
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# UI 경로 추가 (필수!)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

qt_add_executable(hw2
    src/main.cpp
    src/mainwindow.cpp
    include/mainwindow.h
    ui/mainwindow.ui
    include/cupview.h
    src/cupview.cpp
)
target_sources(${PROJECT_NAME} PRIVATE
    src/main.cpp
    src/mainwindow.cpp
    include/mainwindow.h
    include/cupview.h
    src/cupview.cpp
)
target_include_directories(hw2 PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}                  # <-- 자동 생성된 경로
    ${CMAKE_CURRENT_BINARY_DIR}/hw2_autogen/include  # <-- AUTOGEN 헤더 경로 추가
)

target_link_libraries(hw2 PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
)
