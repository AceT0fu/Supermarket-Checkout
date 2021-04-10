cmake_minimum_required(VERSION 3.14)
project(Checkout)

set(CMAKE_CXX_STANDARD 14)

add_executable(Checkout main.cpp Item.cpp Item.h Set.cpp Set.h)