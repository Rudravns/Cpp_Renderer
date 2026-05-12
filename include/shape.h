#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class TriangleRenderer
{
public:
    unsigned int VAO, VBO;
    unsigned int shaderProgram;

    void init();
    void render();
    void cleanup();
};