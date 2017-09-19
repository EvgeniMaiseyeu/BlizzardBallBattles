#include "sprite.h"

Sprite::Sprite(GLuint textureBuffersID) {
  textureBufferID = textureBuffersID;
  position = Vector2();
}

void Sprite::render() {
  glBindTexture(GL_TEXTURE_2D, textureBufferID);
  glDrawArrays(GL_QUADS, 0, 4);
}

Transform Sprite::getTransform() {
  return transform;
}