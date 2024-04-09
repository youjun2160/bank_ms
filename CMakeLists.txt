cmake_minimum_required(VERSION 3.27)
project(bank_ms)

set(CMAKE_CXX_STANDARD 23)

add_executable(bank_ms main.cpp
        tool.cpp
        tool.h)
