#pragma once


#include "GLHeaders.h"
#include "GameObject.h"
#define GL3_PROTOTYPES 1
class GameManager 
{
public:
   GameManager();
   void BeginLoop();
   void EndLoop();
   static GameManager* GetInstance();

   void AddGameObject(int id, GameObject* obj);
   void RemoveGameObject(int id);
   void Update(int ticks);

private:
   std::map<int, GameObject*> gameObjects;
   static GameManager* instance;
   bool breakLoop = false;
   int lastTime = 0;

   bool IsQuitRequested(SDL_Event event);
   void FPSThrottle(int ticks);
};