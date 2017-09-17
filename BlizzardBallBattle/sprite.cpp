#include "sprite.h"

void Sprite::setPosition(Vector2 newPosition) {
  _position = newPosition;
}

void Sprite::SetPosition(float x, float y) {
  Vector2 vector(x, y);
  _position = vector;
}

void Sprite::SetXPosition(float x) {
  Vector2 vector(x, _position.y);
  _position = vector;
}

void Sprite::SetYPosition(float y) {
  Vector2 vector(_position.x, y);
  _position = vector;
}

Vector2 Sprite::getPosition() {
  return _position;
}

Sprite::Sprite(GLuint textureBufferID) {
  _textureBufferID = textureBufferID;
  _position = Vector2();
}

void Sprite::render() {
  glBindTexture(GL_TEXTURE_2D, _textureBufferID);
  glDrawArrays(GL_QUADS, 0, 4);
}

void Sprite::update() {

}