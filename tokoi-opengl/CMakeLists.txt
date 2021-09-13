cmake_minimum_required(VERSION 3.20)
project(opengl_study)

set(CMAKE_CXX_STANDARD 20)

include_directories(..)
add_executable(opengl_study main.cpp Window.cpp)
target_link_libraries(opengl_study glew32 glfw3 opengl32)

#file(GLOB RESOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/resources/*.frag ${CMAKE_CURRENT_SOURCE_DIR}/resources/*.vert)
#file(COPY ${RESOURCES_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resources/)