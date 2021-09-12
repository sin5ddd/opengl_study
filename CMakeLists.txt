cmake_minimum_required(VERSION 3.20)
project(opengl_study)

set(CMAKE_CXX_STANDARD 20)

include_directories(./)
add_executable(opengl_study main.cpp)
target_link_libraries(opengl_study glew32 glfw3 opengl32)
