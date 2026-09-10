cmake_minimum_required(VERSION 4.1)
project(Black_Hole_Renderer)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL3 CONFIG REQUIRED)

add_executable(Black_Hole_Renderer
        main.cpp
        Classes/Window.cpp
        Classes/Window.h
        Classes/Vec3.cpp
        Classes/Vec3.h
        Classes/Ray.cpp
        Classes/Ray.h
        Classes/Camera.cpp
        Classes/Camera.h
        Classes/Sphere.cpp
        Classes/Sphere.h
        HitRecord.cpp
        HitRecord.h)

target_link_libraries(Black_Hole_Renderer PRIVATE SDL3::SDL3)