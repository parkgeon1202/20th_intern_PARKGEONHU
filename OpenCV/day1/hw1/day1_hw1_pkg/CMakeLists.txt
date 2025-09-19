cmake_minimum_required(VERSION 3.5)
project(day1_hw1_pkg)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(ament_cmake REQUIRED)
find_package(OpenCV REQUIRED)


add_executable(opencv_show
  src/image_subscriber.cpp
  src/image_compare.cpp   
)

# 인클루드 경로
target_include_directories(opencv_show PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/include/day1_hw1_pkg
  ${OpenCV_INCLUDE_DIRS}
)

# 링크
target_link_libraries(opencv_show
  ${OpenCV_LIBRARIES}
)

# 설치: 실행 파일
install(TARGETS opencv_show
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)


install(DIRECTORY include/
  DESTINATION include
)
install(DIRECTORY resources/
  DESTINATION share/${PROJECT_NAME}/resources
)

# (선택) 테스트
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
