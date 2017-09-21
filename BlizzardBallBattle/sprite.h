#pragma once


#include <iostream>
#ifdef __APPLE__
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <GLUT/glut.h>
#include <GLFW/glfw3.h>
#elif defined _WIN32 || defined _WIN64
#include <SDL.h>
#include <GL/glut.h>
#include <GL/GL.h>
#endif
#include "transform.h"
#include "shader.h"

struct Vector2
{
  GLfloat x;
  GLfloat y;
  Vector2(float _x, float _y)
  {
    x = _x;
    y = _y;
  }
  Vector2()
  {
    x = 0.0;
    y = 0.0;
  }
};

class Sprite {
private :
  GLuint textureBufferID;
  Vector2 position;
  Vector2 scale;
  float rotation; //0 facing right, 90 down, -90 up, 180 backwards
  Transform* transform;
  Shader* activeShader;

public:
  Transform* getTransform();
  Sprite(GLuint textureBufferID);
  ~Sprite();
  void render();
  void update();
  void setActiveShader(Shader* shader);
  Shader* getShader();
  GLuint getTextureBufferID();
};