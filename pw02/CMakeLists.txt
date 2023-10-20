cmake_minimum_required(VERSION 3.16)
project(heig-prg1-pw02)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wconversion -Wsign-conversion -pedantic")

add_executable(
        Labo02 main.cpp
        montantEnToutesLettres.cpp montantEnToutesLettres.h
)
