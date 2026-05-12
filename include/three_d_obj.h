#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Cube3D
{
public:
    unsigned int VAO, VBO;
    unsigned int shaderProgram;

    void init();
    void render(float time, glm::mat4 view, glm::mat4 projection);
    void cleanup();
};