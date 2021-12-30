cmake_minimum_required(VERSION 3.0.0)
project(compiler)

set(SOURCE_FILES main.cpp gencode.cpp lexic.cpp semantic.cpp syntax.cpp)

add_executable(compiler ${SOURCE_FILES})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/runtime.s
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/runtime.cmm
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})