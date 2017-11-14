#pragma once

#include "AudioManager.h"
#include "Updateable.h"
#include "GLHeaders.h"
#include "GameObject.h"
#define GL3_PROTOTYPES 1
#include "Scene.h"
#include "Game.h"
class GameManager : public Updateable 
{
public:
    GameManager();
    void OnStart();
    void OnUpdate(int ticks);
    void OnEnd();
    static GameManager* GetInstance();

    void AddGameObject(int id, GameObject* obj);
    void RemoveGameObject(int id);

private:
    std::map<int, GameObject*> globalGameObjects;
    static GameManager* instance;
    bool breakLoop = false;
    int lastTime = 0;
    //game instance.
    Game* game;

   bool IsQuitRequested(SDL_Event event);
   void FPSThrottle(int ticks);
};