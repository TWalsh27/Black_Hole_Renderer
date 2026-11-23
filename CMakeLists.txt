cmake_minimum_required(VERSION 4.1)
project(Black_Hole_Renderer)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL3 CONFIG REQUIRED)

add_executable(Black_Hole_Renderer
        main.cpp
        Classes/Renderer_Classes/Window.cpp
        Classes/Renderer_Classes/Window.h
        Classes/Renderer_Classes/Vec3.cpp
        Classes/Renderer_Classes/Vec3.h
        Classes/Renderer_Classes/Ray.cpp
        Classes/Renderer_Classes/Ray.h
        Classes/Renderer_Classes/Camera.cpp
        Classes/Renderer_Classes/Camera.h
        Classes/Renderer_Classes/Sphere.cpp
        Classes/Renderer_Classes/Sphere.h
        Classes/Renderer_Classes/HitRecord.cpp
        Classes/Renderer_Classes/HitRecord.h
        Classes/Renderer_Classes/Material.cpp
        Classes/Renderer_Classes/Material.h
        Classes/Renderer_Classes/Scene.cpp
        Classes/Renderer_Classes/Scene.h
        Classes/Physics_Classes/Integrator.cpp
        Classes/Physics_Classes/Integrator.h
)

target_link_libraries(Black_Hole_Renderer PRIVATE SDL3::SDL3)

enable_testing()

add_executable(test_integrator
        Tests/test_integrator.cpp
        Classes/Physics_Classes/Integrator.cpp
        Classes/Renderer_Classes/Vec3.cpp
)

add_test(NAME IntegratorTest COMMAND test_integrator)