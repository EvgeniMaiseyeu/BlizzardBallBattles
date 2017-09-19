#include "sprite.h"

Sprite::Sprite(GLuint textureBuffersID) {
  textureBufferID = textureBuffersID;
  position = Vector2();
  transform = new Transform();
}

Sprite::~Sprite() {
  if (transform != NULL) {
    delete(transform);
  }
}

void Sprite::render() {
  glBindTexture(GL_TEXTURE_2D, textureBufferID);
  glDrawArrays(GL_QUADS, 0, 4);
}

Transform* Sprite::getTransform() {
  return transform;
}