cmake_minimum_required(VERSION 2.8)
project(ch-8)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(virtual_painter virtual_painter.cpp)
target_link_libraries(virtual_painter ${OpenCV_LIBS})

add_executable(color_picker color_picker.cpp)
target_link_libraries(color_picker ${OpenCV_LIBS})