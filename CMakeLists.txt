cmake_minimum_required(VERSION 3.1)
project(sin5ddd-opengl-study)

SET(COMMON_CLASSES_ROOT "${CMAKE_SOURCE_DIR}/common_classes")
SET(GLAD_ROOT "${CMAKE_SOURCE_DIR}/external/glad")
SET(GLAD_INCLUDE_DIRS "${GLAD_ROOT}/include")
#SET(GLAD_INCLUDE_SOURCE_FILES "${GLAD_ROOT}/src/glad.c")
#SET(GLAD_INCLUDE_HEADER_FILES "${GLAD_INCLUDE_DIRS}/glad/glad.h")

add_subdirectory(${GLAD_ROOT})

add_subdirectory(tokoi-opengl)
add_subdirectory(opengl4-tutorial)