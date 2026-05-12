#pragma once
#include <string>

std::string loadFile(const std::string& path);
unsigned int compileShader(unsigned int type, const std::string& source);
unsigned int createShader(const std::string& vertexPath, const std::string& fragmentPath);