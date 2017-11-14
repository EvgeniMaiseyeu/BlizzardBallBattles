#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "GLHeaders.h"

using namespace std;

class Shader {
public:
  GLuint Program;
  Shader(const GLchar *vertexPath, const GLchar *fragmentPath);
  void Use();
};
