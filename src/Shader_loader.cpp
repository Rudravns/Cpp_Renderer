#include "Shader_loader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <iostream>

std::string loadFile(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        std::cout << "Failed to open: " << path << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

unsigned int compileShader(unsigned int type, const std::string& source)
{
    unsigned int shader = glCreateShader(type);
    const char* src = source.c_str();

    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "Shader compile error:\n" << infoLog << std::endl;
    }

    return shader;
}

unsigned int createShader(const std::string& vertexPath, const std::string& fragmentPath)
{
    std::string vertexCode = loadFile(vertexPath);
    std::string fragmentCode = loadFile(fragmentPath);
    // STOP IF FILE FAILED
    if (vertexCode.empty() || fragmentCode.empty())
    {
        std::cout << "Shader creation aborted (missing file)\n";
        return 0;
    }

    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexCode);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentCode);

    unsigned int program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cout << "Program link error:\n" << infoLog << std::endl;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}