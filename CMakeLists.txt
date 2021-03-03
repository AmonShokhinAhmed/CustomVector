cmake_minimum_required(VERSION 3.1.5)

project(
    CustomVector
    VERSION 1.0
    DESCRIPTION "Reimplementing the std::vector class for my Game Engine Design class."
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(SRC_DIR src)
set(RUNTIME_DIR ${CMAKE_BINARY_DIR}/bin)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${RUNTIME_DIR})

file(
    GLOB_RECURSE 
    SRCFILES 
    RELATIVE ${CMAKE_SOURCE_DIR} 
    CONFIGURE_DEPENDS
    "${SRC_DIR}/*.cpp"
    "${SRC_DIR}/*.c"
    "${SRC_DIR}/*.h"
    "${SRC_DIR}/*.hpp"
)

add_executable(${PROJECT_NAME}
    ${SRCFILES}
    )