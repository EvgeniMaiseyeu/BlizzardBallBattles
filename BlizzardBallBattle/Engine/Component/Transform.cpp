#include "Transform.h"

Transform::operator GLfloat*() {
  if (values == NULL) {
    values = new GLfloat[16]{
      1, 0, 0, 0,
      0, 1, 0, 0,
      0, 0, 1, 0,
      0, 0, 0, 1
    };
  }

  float scaleRotCos = scale / GAME_WIDTH * 2.0 * cos(rotation * 3.14159 / 180.0);
  float scaleRotSin = scale / GAME_WIDTH * 2.0 * sin(rotation * 3.14159 / 180.0);

  float glX = x;
  float glY = y;
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
  scale = 1.0f;
  x = 0.0f;
  y = 0.0f;
  rotation = 0.0f;
  values = NULL;
}

Transform::~Transform() {
  if (values != NULL) {
    delete(values);
  }
}

void Transform::addTranslation(float xToAdd, float yToAdd) {
  x += xToAdd;
  y += yToAdd;
}

void Transform::setPosition(float newX, float newY) {
  x = newX;
  y = newY;
}

void Transform::addX(float xToAdd) {
  x += xToAdd;
}

void Transform::addY(float yToAdd) {
  y += yToAdd;
}

void Transform::setX(float newX) {
  x = newX;
}

void Transform::setY(float newY) {
  y = newY;
}

void Transform::addRotation(float byDegrees) {
  rotation += byDegrees;
}

void Transform::setRotation(float newAngle) {
  rotation = newAngle;
}

void Transform::addScale(float scaleToAdd) {
  scale += scaleToAdd;
}

void Transform::setScale(float newScale) {
  scale = newScale;
}

float Transform::getX() {
  return x;
}

float Transform::getY() {
  return y;
}

float Transform::getRotation() {
  return rotation;
}

float Transform::getScale() {
  return scale;
}