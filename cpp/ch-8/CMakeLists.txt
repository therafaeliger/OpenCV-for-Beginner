cmake_minimum_required(VERSION 2.8)
project(ch-8)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(ch-8 ch-8.cpp)
target_link_libraries(ch-8 ${OpenCV_LIBS})
