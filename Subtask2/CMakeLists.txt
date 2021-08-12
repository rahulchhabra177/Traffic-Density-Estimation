cmake_minimum_required(VERSION 3.1)

project(COP_Subtask2)

find_package(OpenCV REQUIRED)

add_executable(video video.cpp)

target_link_libraries(video PRIVATE ${OpenCV_LIBS})
