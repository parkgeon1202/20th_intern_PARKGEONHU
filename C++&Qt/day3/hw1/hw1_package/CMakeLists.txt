cmake_minimum_required(VERSION 3.16)  # Qt6 권장. Qt5만 쓸 거면 3.5도 OK

project(hw1_package LANGUAGES CXX)            # 실행 파일 이름도 hw2가 됨 (=${PROJECT_NAME})

# 기본 설정(자동 MOC/UIC/RCC)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# C++ 표준 (필요시 17로 올리세요)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt5/Qt6 자동 탐지
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# UIC가 .ui를 찾을 기본 폴더
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)

# 소스 목록(필요한 것만 간단히)
set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
    include/mainwindow.h
    ui/mainwindow.ui
)

# 타겟 생성: 항상 프로젝트 이름을 타겟명으로 사용
if (QT_VERSION_MAJOR EQUAL 6)
    qt_add_executable(${PROJECT_NAME} ${SOURCES})
else()
    add_executable(${PROJECT_NAME} ${SOURCES})
endif()

# 인클루드 경로 최소화
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 링크
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
)
