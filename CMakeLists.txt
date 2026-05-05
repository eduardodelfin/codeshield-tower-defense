cmake_minimum_required(VERSION 3.16)

project(CODESHIELD LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_COMPILER clang++)

add_executable(CODESHIELD
    src/main.cpp
)

target_include_directories(CODESHIELD PRIVATE include)
