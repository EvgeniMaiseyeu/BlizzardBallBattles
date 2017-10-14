#pragma once

#include "SpriteRendererManager.h"
#include "MatchManager.h"

#include "GLHeaders.h"
#define GL3_PROTOTYPES 1
#include <stdio.h>
#include <string>
#include <iostream>
#include "GameManager.h"
#include "MessageManager.h"

class GameManager 
{
public:
    GameManager();
    void BeginLoop();
    void EndLoop();
    static GameManager* GetInstance();

    void AddGameObject(int id, GameObject* obj);
    void RemoveGameObject(int id);

private:
    std::map<int, GameObject*> gameObjects;
    static GameManager* instance;
    bool breakLoop = false;
    int lastTime = 0;

    void Update(int ticks);
    bool IsQuitRequested(SDL_Event event);
    void FPSThrottle(int ticks);
};