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
    while (!breakLoop)
    {
        int curTime = SDL_GetTicks();
        int ticks = curTime - lastTime;
        lastTime = curTime;
        //update system managers then.
        OnUpdate(ticks);
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
        InputManager::GetInstance()->HandlePolledEvent(event);
        breakLoop = IsQuitRequested(event);
    }

    if (NetworkingManager::GetInstance()->IsConnected()) {
        std::string tmp;
        if (NetworkingManager::GetInstance()->GetMessage(tmp)) {
            NetworkingManager::GetInstance()->HandleParsingEvents(tmp);
        }
    
        NetworkingManager::GetInstance()->SendQueuedEvents();
    }
 
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
 
bool GameManager::IsQuitRequested(SDL_Event event)
{
    return (event.type == SDL_QUIT || event.type == SDL_KEYDOWN);
}
 
void GameManager::AddGameObject(int id, GameObject* obj) {
    globalGameObjects[id] = obj;
}
 
void GameManager::RemoveGameObject(int id) {
    globalGameObjects.erase(id);
}