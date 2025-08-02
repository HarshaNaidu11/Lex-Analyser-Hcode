cmake_minimum_required(VERSION 3.10)
project(HcodeCompiler)

set(CMAKE_CXX_STANDARD 17)

add_executable(HcodeCompiler main.cpp
    src/lexer.cpp
)
