cmake_minimum_required(VERSION 3.16)

project(CODESHIELD LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_COMPILER clang++)

find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system)

add_executable(CODESHIELD
    src/main.cpp
    src/MatrizJuego.cpp
    src/GestorTorres.cpp
    src/GestorEnemigos.cpp
)

target_include_directories(CODESHIELD PRIVATE include)

target_link_libraries(CODESHIELD
    PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)
