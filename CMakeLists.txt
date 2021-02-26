cmake_minimum_required(VERSION 3.2)

project(L02_cpp_basics_demo)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(constants src/constants.cpp)
add_executable(enums src/enums.cpp)