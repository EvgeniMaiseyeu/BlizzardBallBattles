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
    spriteRenderer->SetActiveSprite(sprite);
    if (nonDefaultShader == nullptr) {
        shader = new Shader(BuildPath("Game/Assets/Shaders/vertex_shader.vs").c_str(), BuildPath("Game/Assets/Shaders/fragment_shader.fs").c_str());
    } else {
        shader = nonDefaultShader;
    }
    AddComponent<SpriteRenderer*>(spriteRenderer);
    spriteRenderer->SetActiveSprite(sprite);
    spriteRenderer->SetActiveShader(shader);
    transform->setPosition(x, y, z);
    transform->setScale(scale);
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