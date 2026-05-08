cmake_minimum_required(VERSION 3.20)

project(Renderer)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

# GLFW
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
)

FetchContent_MakeAvailable(glfw)

include_directories(include)

add_executable(Renderer
        main.cpp
        src/gl.c
)

target_link_libraries(Renderer
        glfw
        opengl32
)