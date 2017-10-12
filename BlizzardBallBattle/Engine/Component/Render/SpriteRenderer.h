#pragma once

#include "GameObject.h"
#include "Component.h"
#include "Shader.h"
#include "ISprite.h"

class SpriteRenderer : public Component {
private:
  GLuint textureBufferID;
  Shader* activeShader;
  ISprite* activeSprite;

public:
    SpriteRenderer(GameObject* gameObject);
    void Render();
    void SetActiveShader(Shader* shader);
    void SetActiveSprite(ISprite* sprite);
    Shader* GetShader();
    ISprite* GetSprite();
};