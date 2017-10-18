#include "LaunchMenuScene.h"
#include "HelperFunctions.h"
#include "InputManager.h"
#include "GLHeaders.h"

void LaunchMenuScene::OnStart() {
    BuildBaseScene();
    menuTitle = new SimpleSprite("Title.png", 0.0f, getGameTopY() - getGameHeight()/3.0f, 0.0f, GAME_WIDTH, pixelShader);
    howToText = new SimpleSprite("HowTo.png", 0.0f, -getGameHeight() / 6.0f, 1.0f, GAME_WIDTH / 1.5f, pixelShader);
}

LaunchMenuScene::~LaunchMenuScene() {
    delete(menuTitle);
    delete(howToText);
}


void LaunchMenuScene::OnUpdate(int ticks) {
    InputManager* inputManager = InputManager::GetInstance();
    if (inputManager->onKeyPressed(SDLK_h)) {
        //Host
    } else if (inputManager->onKeyPressed(SDLK_j)) {
        //Join
    } else if (inputManager->onKeyPressed(SDLK_1)) {
        //1 player
    } else if (inputManager->onKeyPressed(SDLK_2)) {
        //2 player
    }
}