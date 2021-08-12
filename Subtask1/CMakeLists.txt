cmake_minimum_required(VERSION 3.1)

project(COP_Subtask1)

find_package(OpenCV REQUIRED)

add_executable(img img.cpp)

target_link_libraries(img PRIVATE ${OpenCV_LIBS})
