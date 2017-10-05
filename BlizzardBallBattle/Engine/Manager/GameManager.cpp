#include "GameManager.h"

void GameManager::Update(int ticks) {
    SpriteRendererManager.getInstance().update(ticks);
}
