#pragma once

#include <GL/glew.h>
#include <math.h>
#include "HelperFunctions.h"
#include <iostream>
#include "Component.h"

class Transform : public Component {
private:
  float x;
  float y;
  float rotation;
  float scale;
  GLfloat* values;

public:
  Transform(GameObject* gameObject);
  ~Transform();
  void addTranslation(float xToAdd, float yToAdd);
  void addX(float xToAdd);
  void addY(float yToAdd);
  void setX(float newX);
  void setY(float newY);
  void setPosition(float newX, float newY);
  void addRotation(float byDegrees);
  void setRotation(float newAngle);
  void addScale(float scaleToAdd);
  void setScale(float newScale);
  float getX();
  float getY();
  float getRotation();
  float getScale();
  operator GLfloat*();
};