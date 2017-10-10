#include "SpriteRenderer.h"
#include "SpriteRendererManager.h"

SpriteRenderer::SpriteRenderer(GameObject* gameObject) : Component(gameObject) {
  SpriteRendererManager::GetInstance()->AddSpriteForRendering(this); //.subscribe(gameObject.id, this); NOTE: Not subscribing/unsubscribing for now
}

void SpriteRenderer::Render() {
  glBindTexture(GL_TEXTURE_2D, textureBufferID);
  glDrawArrays(GL_QUADS, 0, 4);
}

void SpriteRenderer::SetActiveShader(Shader* shader) {
  activeShader = shader;
}

void SpriteRenderer::SetActiveTexture(GLuint textureBufferID) {
  this->textureBufferID = textureBufferID;
}

Shader* SpriteRenderer::GetShader() {
  return activeShader;
}

GLuint SpriteRenderer::GetTextureBufferID() {
  return textureBufferID;
}