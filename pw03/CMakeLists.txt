cmake_minimum_required(VERSION 3.16)
project(heig-prg1-pw03)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wconversion -Wsign-conversion -pedantic")

add_executable(L3-LongMath main.cpp lm_tostring.cpp lm_fromstring.cpp lm_add.cpp lm_multiply.cpp helper.cpp)
add_subdirectory(Test)
