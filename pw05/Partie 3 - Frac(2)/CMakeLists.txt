cmake_minimum_required(VERSION 3.16)
project(PRG1-D21-L5-Fractions)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wconversion -Wsign-conversion -pedantic")

add_executable(Frac2 main.cpp Frac.h FracImpl.h FracTypeChooser.h)
