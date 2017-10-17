#include "GameManager.h"
#include "InputManager.h"
#include "SpriteRendererManager.h"
#include "MatchManager.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include "MessageManager.h"
#include "NetworkingManager.h"
 
GameManager* GameManager::instance;
 
GameManager* GameManager::GetInstance() {
    if (instance == NULL)
        instance = new GameManager();
    return instance;
}
 
GameManager::GameManager() {
 
}
 
void GameManager::BeginLoop(Scene* scene)
{
	scene->OnStart();
    lastTime = SDL_GetTicks();
    while (!breakLoop)
    {
        int curTime = SDL_GetTicks();
        int ticks = curTime - lastTime;
        lastTime = curTime;
        Update(ticks);
        scene->OnUpdate();
    }
    scene->OnEnd();
}
 
bool isConnected = false;

void GameManager::Update(int ticks)
{
 
    //Handle SDL Events
    InputManager::GetInstance()->UpdateKeys();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        InputManager::GetInstance()->HandlePolledEvent(event);
        breakLoop = IsQuitRequested(event);
    }

    if (InputManager::GetInstance()->onKeyPressed(SDLK_h)) {
        NetworkingManager::GetInstance()->CreateHost();
        isConnected = true;
      }
      
      if (InputManager::GetInstance()->onKeyPressed(SDLK_j)) {
        NetworkingManager::GetInstance()->CreateClient();
        isConnected = true;
      }

    if (isConnected) {
        std::string tmp;
        if (NetworkingManager::GetInstance()->GetMessage(tmp))
            NetworkingManager::GetInstance()->HandleParsingEvents(tmp);
    
        NetworkingManager::GetInstance()->SendQueuedEvents();
    }
 
    SpriteRendererManager::GetInstance()->Update(ticks);
 
    

    for (std::map<int, GameObject*>::iterator it=gameObjects.begin(); it!=gameObjects.end(); ++it) {
        it->second->Update(ticks);
    }
 
    FPSThrottle(ticks);
 


    //Temporary place where we update GameObjects
    //player1->GetComponent<Transform *>()->addRotation(0.5f);
}
 
void GameManager::EndLoop()
{
    breakLoop = true;
}
 
void GameManager::FPSThrottle(int ticks) {
    int delay = 1000 / MAX_FPS - ticks;
    if (delay > 0) {
        SDL_Delay(delay);
    }
}
 
bool GameManager::IsQuitRequested(SDL_Event event)
{
    return (event.type == SDL_QUIT || event.type == SDL_KEYDOWN);
}
 
void GameManager::AddGameObject(int id, GameObject* obj) {
    gameObjects[id] = obj;
}
 
void GameManager::RemoveGameObject(int id) {
    gameObjects.erase(id);
}