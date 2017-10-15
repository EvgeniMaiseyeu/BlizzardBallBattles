#include "GameManager.h"

GameManager::GameManager() 
{
    SpriteRendererManager::GetInstance();
    MatchManager::GetInstance()->StartGame();
    
}

void GameManager::Update(int ticks) 
{
    SpriteRendererManager::GetInstance()->Update(ticks);
}