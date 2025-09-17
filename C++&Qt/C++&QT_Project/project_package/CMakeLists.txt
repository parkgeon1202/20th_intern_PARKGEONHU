cmake_minimum_required(VERSION 3.16)

project(project_package VERSION 1.0 LANGUAGES CXX)

# ---- C++ / Qt 자동 생성기 ----
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# ui/ 경로의 .ui 검색
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui)

# ---- Qt 찾기 (Qt6 우선, 없으면 Qt5) ----
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

# ---- 소스 ----
set(APP_SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/drawingcanvas.cpp
    include/mainwindow.h
    include/drawingcanvas.h
    ui/mainwindow.ui
)

# ---- 리소스(qrc) ----
# Qt6: qt_add_resources / Qt5: qt5_add_resources
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_resources(APP_RESOURCES resources/resources.qrc)
else()
    qt5_add_resources(APP_RESOURCES resources/resources.qrc)
endif()

# ---- 실행 파일 ----
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME} MANUAL_FINALIZATION
        ${APP_SOURCES}
        ${APP_RESOURCES}
    )
else()
    add_executable(${PROJECT_NAME}
        ${APP_SOURCES}
        ${APP_RESOURCES}
    )
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
)

# Qt6 마무리
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()
