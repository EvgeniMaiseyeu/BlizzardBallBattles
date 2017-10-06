#include "GameManager.h"

GameManager::GameManager() {
    SpriteRendererManager.GetInstance();
}

void GameManager::Update(int ticks) {
    SpriteRendererManager.GetInstance().update(ticks);
}
