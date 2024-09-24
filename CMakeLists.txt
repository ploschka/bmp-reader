cmake_minimum_required(VERSION 3.13)
project(bmp-reader
    VERSION 0.0.1
    DESCRIPTION "Read bmp files and print them in console"
    LANGUAGES CXX
    )

set(exename bmpreader)

add_executable(${exename} main.cpp)

