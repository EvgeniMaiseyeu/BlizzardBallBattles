#include "MenuScene_Alpha.h"
#include "SpriteRendererManager.h"
#include "HelperFunctions.h"
#include "SharedConstants.h"
#include "Sprite.h"
#include "SpriteRenderer.h"
#include "Transform.h"

void MenuScene_Alpha::OnEnd() {
    DestroyBaseScene();
}

void MenuScene_Alpha::BuildBaseScene() {
    pixelShader = new Shader(BuildPath("Game/Assets/Shaders/vertex_shader.vs").c_str(), BuildPath("Game/Assets/Shaders/voxel.fs").c_str());
    menuBackground = new SimpleSprite("Sky.png", 0.0f, 0.0f, -2, GAME_WIDTH, pixelShader);
    menuForeground = new SimpleSprite("ForegroundTrees.png", 0.0f, -getGameHeight()/5.0f, -1, GAME_WIDTH, pixelShader);
}

void MenuScene_Alpha::DestroyBaseScene() {
    //delete(pixelShader);
    menuBackground->GetComponent<Transform*>()->setScale(0.0f);
    //delete(menuBackground);
    menuForeground->GetComponent<Transform*>()->setScale(0.0f);
    //delete(menuForeground);
}