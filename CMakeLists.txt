cmake_minimum_required(VERSION 3.0.0)
project(compiler)

set(SOURCE_FILES main.cpp gencode.cpp lexic.cpp semantic.cpp syntax.cpp)

add_executable(compiler ${SOURCE_FILES})