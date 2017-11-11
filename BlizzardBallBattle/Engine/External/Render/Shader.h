#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "GLHeaders.h"
#include "HelperFunctions.h"
#include <map>

using namespace std;

#define SHADER_DEFAULT 0
#define SHADER_PIXEL 1
#define SHADER_TILE 2
#define SHADER_SPRITESHEET 3

class Shader {
private:
  int shaderID;
  static std::map<int, Shader*> createdShaders;

public:
  GLuint Program;
  void Use();
  int GetID();
  Shader(const GLchar *vertexPath, const GLchar *fragmentPath, int id);
  static Shader* GetShader(int shaderID = SHADER_DEFAULT);  
};
