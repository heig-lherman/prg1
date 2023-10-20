cmake_minimum_required(VERSION 3.16)
project(heig-prg1-pw01)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wconversion -Wsign-conversion -pedantic")

add_executable(Main1 main1.cpp)
add_executable(Main2 main2.cpp)
