#pragma once

#include "Component.h"
#include "Shader.h"

class SpriteRenderer : public Component {
private:
  GLuint textureBufferID;
  Shader* activeShader;

public:
    SpriteRenderer(GameObject* gameObject);
    void Render();
    void SetActiveShader(Shader* shader);
    void SetActiveTexture(GLuint textureBufferID);
    Shader* GetShader();
    GLuint GetTextureBufferID();
};