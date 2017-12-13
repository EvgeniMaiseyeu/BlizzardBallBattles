#include "SimpleSprite.h"
#include "SpriteRendererManager.h"
#include "Sprite.h"
#include "Transform.h"
#include "Shader.h"
#include "HelperFunctions.h"

SimpleSprite::SimpleSprite(std::string path, float x, float y, float z, float scale, Shader* nonDefaultShader) : GameObject(false) { 
    std::string totalPath("Game/Assets/Sprites/" + path);
    GLuint titleTexture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath((char*)totalPath.c_str()));
	sprite = new Sprite(titleTexture);
    SpriteRenderer* spriteRenderer = new SpriteRenderer(this);
    Transform* transform = GetTransform();
    if (nonDefaultShader != nullptr) {
        shader = nonDefaultShader;
        spriteRenderer->SetActiveShader(shader);
    }
    spriteRenderer->SetActiveSprite(sprite);
    transform->setPosition(x, y, z);
    transform->setScale(scale);
	AddComponent<SpriteRenderer*>(spriteRenderer);
}

/*SimpleSprite::~SimpleSprite() {
    if (sprite != nullptr) {
       delete(sprite);
    }
}*/