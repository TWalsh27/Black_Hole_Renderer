cmake_minimum_required(VERSION 4.1)
project(untitled1)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 CONFIG REQUIRED)

add_executable(untitled1 main.cpp
        Window.cpp
        Window.h
        Vec3.cpp
        Vec3.h
        Ray.cpp
        Ray.h)

target_link_libraries(untitled1 PRIVATE SDL2::SDL2main SDL2::SDL2)