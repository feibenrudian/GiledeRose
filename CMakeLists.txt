cmake_minimum_required(VERSION 3.15)
project(GileRoss)

set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME} GileRossMain.cpp ./src/SellingManager.cc)
add_subdirectory(tests)