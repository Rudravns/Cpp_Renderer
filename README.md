# Cpp_Renderer

A modern OpenGL renderer / mini game engine written in C++ using GLFW, GLAD, GLM, CMake, and vcpkg.

---

# Features

- Modern OpenGL 3.3 Core
- FPS camera system
- WASD movement
- Mouse look
- Toggle cursor with `P`
- Rotating 3D cube renderer
- GLSL shader loading system
- Depth testing
- Dynamic fullscreen/window resizing
- CMake build system
- vcpkg dependency management
- Visual Studio 2026 compatible

---

# Controls

| Key | Action |
|---|---|
| W | Move Forward |
| S | Move Backward |
| A | Move Left |
| D | Move Right |
| Mouse | Look Around |
| P | Toggle Cursor |
| ESC | Exit |

---

# Project Structure

```text
Cpp_Renderer/
│
├── include/
│   ├── camera.h
│   ├── Shader_loader.h
│   └── three_d_obj.h
│
├── src/
│   ├── camera.cpp
│   ├── Shader_loader.cpp
│   ├── math.cpp
│   ├── shape.cpp
│   └── three_d_obj.cpp
│
├── Shaders/
│   ├── cube.vert
│   └── cube.frag
│
├── out/
│
├── CMakeLists.txt
├── vcpkg.json
├── .gitignore
└── README.md
