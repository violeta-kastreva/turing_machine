cmake_minimum_required(VERSION 3.24)
project(turing_machine)

set(CMAKE_CXX_STANDARD 17)

add_executable(turing_machine doctest.h turingmachine.h tests.cpp turingmachine.cpp)
