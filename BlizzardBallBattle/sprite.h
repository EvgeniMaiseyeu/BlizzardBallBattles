#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/GL.h>
#include "transform.h"

struct Vector2 {
  GLfloat x;
  GLfloat y;
  Vector2(float _x, float _y) {
    x = _x;
    y = _y;
  }
  Vector2() {
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
  Transform transform;

public:
  Transform getTransform();
  Sprite(GLuint textureBufferID);
  void render();
  void update();
};