#pragma once

#include <GL/glew.h>
#include <math.h>
#include "HelperFunctions.h"
#include <iostream>
#include "Component.h"

class Transform : public Component {
private:
  float _x;
  float _y;
  float _rotation;
  float _scale;
  GLfloat* values;

public:
  Transform(GameObject* gameObject);
  ~Transform();
  void addTranslation(float xToAdd, float yToAdd);

  __declspec (property (put = setX, get = getX)) float x;
  void setX(float newX);
  float getX();

  __declspec (property (put = setY, get = getY)) float y;
  void setY(float newY);
  float getY();
  
  void setPosition(float newX, float newY);

  __declspec (property (put = setScale, get = getScale)) float scale;
  void setScale(float newScale);
  float getScale();

  __declspec (property (put = setRotation, get = getRotation)) float rotation;
  void setRotation(float newAngle);
  float getRotation();
  operator GLfloat*();
};