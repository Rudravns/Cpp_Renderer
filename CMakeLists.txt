cmake_minimum_required(VERSION 3.20)

project(Renderer)

set(CMAKE_CXX_STANDARD 20)

# -------------------------
# Dependencies
# -------------------------
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

# -------------------------
# Executable
# -------------------------
add_executable(Renderer
    main.cpp
    src/math.cpp
    src/shape.cpp
    src/Shader_loader.cpp
    src/camera.cpp
    src/three_d_obj.cpp
 "include/three_d_obj.h" "src/three_d_obj.cpp")

# -------------------------
# Include directories
# -------------------------
target_include_directories(Renderer PRIVATE
    include
    src
)

# -------------------------
# Link libraries
# -------------------------
target_link_libraries(Renderer
    glfw
    glad::glad
    glm::glm
    opengl32
)

# -------------------------
# Output directory
# -------------------------
set_target_properties(Renderer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin/Debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/Release"
)
