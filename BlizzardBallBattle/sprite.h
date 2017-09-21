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

class Sprite
{
private:
  GLuint _textureBufferID;
  Vector2 _position;
  Vector2 _scale;
  float _rotation; //0 facing right, 90 down, -90 up, 180 backwards

public:
  void setPosition(Vector2 newPosition);
  void SetPosition(float x, float y);
  void SetXPosition(float x);
  void SetYPosition(float y);
  Vector2 getPosition();
  Sprite(GLuint textureBufferID);
  void render();
  void update();
};