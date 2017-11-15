#include "SimpleSprite.h"
#include "SpriteRendererManager.h"
#include "Sprite.h"
#include "Transform.h"
#include "Shader.h"
#include "HelperFunctions.h"

SimpleSprite::SimpleSprite(std::string path, float x, float y, float z, float scale, Shader* nonDefaultShader) : GameObject(false) {
    std::string totalPath("Game/Assets/Sprites/" + path);
    GLuint titleTexture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath((char*)totalPath.c_str()));
    SpriteRenderer* spriteRenderer = new SpriteRenderer(this);
    sprite = new Sprite(titleTexture);
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

SimpleSprite::~SimpleSprite() {
    GetTransform()->setScale(0.0f);
	GetTransform()->setPosition(100000, 1000000, -1000000);
    //TODO: Memory leak fix
    //if (sprite != nullptr) {
    //    delete(sprite);
    //}
    //if (shader != nullptr) {
    //    delete(shader);
    //}
}