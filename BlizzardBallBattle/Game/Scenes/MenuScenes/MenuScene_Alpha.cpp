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
    menuBackground = new SimpleSprite("Sky.png", 0.0f, 0.0f, -2, GAME_WIDTH, Shader::GetShader(SHADER_PIXEL));
    menuForeground = new SimpleSprite("ForegroundTrees.png", 0.0f, -getGameHeight()/5.0f, -1, GAME_WIDTH, Shader::GetShader(SHADER_PIXEL));
}

void MenuScene_Alpha::DestroyBaseScene() {
    //delete(pixelShader);
    menuBackground->GetTransform()->setScale(0.0f);
    //delete(menuBackground);
    menuForeground->GetTransform()->setScale(0.0f);
    //delete(menuForeground);
	Purge();
}