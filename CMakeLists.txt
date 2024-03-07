cmake_minimum_required(VERSION 3.28.3)
project(PreciousMoment VERSION 1.0.0)
cmake_policy(SET CMP0072 NEW)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)

add_executable(PreciousMoment
    src/config.h
    src/config.cpp
    src/main.cpp 
    src/glad.c
    src/factories/factory.cpp
    src/systems/camera_system.cpp
    src/systems/motion_system.cpp
    src/systems/render_system.cpp
    src/view/shader.cpp
    src/controller/app.cpp
)

target_include_directories(PreciousMoment 
    PRIVATE
    Dependencies 
)

target_link_libraries(PreciousMoment
    glfw
    OpenGL::GL 
)