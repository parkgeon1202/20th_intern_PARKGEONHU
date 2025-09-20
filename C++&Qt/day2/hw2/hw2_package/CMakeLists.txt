cmake_minimum_required(VERSION 3.5)

project(hw2_package LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)   # moc 자동
set(CMAKE_AUTOUIC ON)   # ui 자동 (★ 중요)
set(CMAKE_AUTORCC ON)   # qrc 자동
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui)

set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/cupview.cpp        # armview 소스 추가
)

set(HEADERS
    include/mainwindow.h
    include/cupview.h      # armview 헤더 추가
)

set(UI
    ui/mainwindow.ui       # UI 파일 추가
)

add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    ${UI}
)

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)
