#include "Transform.h"

Transform::operator GLfloat*() {
  if (values == nullptr) {
    values = new GLfloat[16]{
      1, 0, 0, 0,
      0, 1, 0, 0,
      0, 0, 1, 0,
      0, 0, 0, 1
    };
  }

  float scaleRotCos = _scale / GAME_WIDTH * 2.0 * cos(_rotation * 3.14159 / 180.0);
  float scaleRotSin = _scale / GAME_WIDTH * 2.0 * sin(_rotation * 3.14159 / 180.0);

  float glX = _x;
  float glY = _y;
  worldPositionToOpenGLPosition(&glX, &glY);

  values[0] = scaleRotCos;
  values[1] = -scaleRotSin;
  values[4] = scaleRotSin;
  values[5] = scaleRotCos;
  values[12] = glX;
  values[13] = glY;

  return values;
}

Transform::Transform(GameObject* gameObject) : Component(gameObject) {
  _scale = 1.0f;
  _x = 0.0f;
  _y = 0.0f;
  _rotation = 0.0f;
  values = NULL;
}

Transform::~Transform() {
  if (values != NULL) {
    delete(values);
  }
}

void Transform::addTranslation(float xToAdd, float yToAdd) {
  _x += xToAdd;
  _y += yToAdd;
}

void Transform::setPosition(float newX, float newY) {
  _x = newX;
  _y = newY;
}

void Transform::setX(float newX) {
  _x = newX;
}

void Transform::setY(float newY) {
  _y = newY;
}

void Transform::setRotation(float newAngle) {
  _rotation = newAngle;
}

void Transform::setScale(float newScale) {
  _scale = newScale;
}

float Transform::getX() {
  return _x;
}

float Transform::getY() {
  return _y;
}

float Transform::getRotation() {
  return _rotation;
}

float Transform::getScale() {
  return _scale;
}
