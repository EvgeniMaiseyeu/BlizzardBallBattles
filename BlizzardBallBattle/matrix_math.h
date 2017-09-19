#pragma once

#include <GL/glew.h>
#include <math.h>

class Transform {
private:
  float x;
  float y;
  float rotation;
  float scale;
  GLfloat* values;

public:
  Transform() {
    x = 0.5f;
    y = 0.5f;
    scale = 0.5f;
    rotation = 0.0f;
  }
  ~Transform() {
    if (values != NULL) {
      delete(values);
    }
  }

  void addTranslate(float xToAdd, float yToAdd) {
    x += xToAdd;
    y += yToAdd;
  }

  void setTranslation(float newX, float newY) {
    x = newX;
    y = newY;
  }

  void addRotation(float byDegrees) {
    rotation += byDegrees;
  }

  void setRotation(float newAngle) {
    rotation = newAngle;
  }

  void addScale(float scaleToAdd) {
    scale += scaleToAdd;
  }

  void setScale(float newScale) {
    scale = newScale;
  }

  operator GLfloat*() { 
    if (values == NULL) {
      values = new GLfloat[16]{
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
      };
    }

    float scaleRotCos = scale * cos(rotation);
    float scaleRotSin = scale * sin(rotation);

    values[0] = scaleRotCos;
    values[1] = -scaleRotSin;
    values[4] = scaleRotSin;
    values[5] = scaleRotCos;
    values[12] = x;
    values[13] = y;

    return values;
  }
};