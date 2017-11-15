#include "GameManager.h"
#include "InputManager.h"
#include "SpriteRendererManager.h"
#include "MatchManager.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include "MessageManager.h"
#include "NetworkingManager.h"
#include "SceneManager.h"
#include "PhysicsManager.h"
 
GameManager* GameManager::instance;
 
GameManager* GameManager::GetInstance() {
    if (instance == NULL)
        instance = new GameManager();
    return instance;
}
 
GameManager::GameManager() {
 
}
 
void GameManager::OnStart()
{
	
    lastTime = SDL_GetTicks();
    game = new Game();
    game->OnStart();
	PhysicsManager::GetInstance()->OnStart();
    while (!breakLoop)
    {
        int curTime = SDL_GetTicks();
        int ticks = curTime - lastTime;
        lastTime = curTime;
        //update system managers then.
        OnUpdate(ticks);
        std::cout << ticks << std::endl;
        //update game.
        SceneManager::GetInstance()->UpdateScene(ticks);
    }
}

void GameManager::OnUpdate(int ticks)
{
 
    //Handle SDL Events
    InputManager::GetInstance()->UpdateKeys();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                breakLoop = true;
                break;
            default:
                InputManager::GetInstance()->HandlePolledEvent(event);
                break;
        }
    }

    if (NetworkingManager::GetInstance()->IsConnected()) {
        std::string tmp;
        while (NetworkingManager::GetInstance()->GetMessage(tmp)) {
            NetworkingManager::GetInstance()->HandleParsingEvents(tmp);
        }
    
        NetworkingManager::GetInstance()->SendQueuedEvents();
    }
 
    PhysicsManager::GetInstance()->OnUpdate(ticks);
    SpriteRendererManager::GetInstance()->OnUpdate(ticks);    

    for (std::map<int, GameObject*>::iterator it=globalGameObjects.begin(); it!=globalGameObjects.end(); ++it) {
        it->second->OnUpdate(ticks);
    }

    game->OnUpdate(ticks);
 
    FPSThrottle(ticks);
}
 
void GameManager::OnEnd()
{
    game->OnEnd();
    breakLoop = true;
}
 
void GameManager::FPSThrottle(int ticks) {
    int delay = FRAME_RATE - ticks;    
    if (delay > 0)
        SDL_Delay(delay);
}
 
void GameManager::AddGameObject(int id, GameObject* obj) {
    globalGameObjects[id] = obj;
}
 
void GameManager::RemoveGameObject(int id) {
    globalGameObjects.erase(id);
	SceneManager::GetInstance()->GetCurrentScene()->RemoveGameObject(id);
}