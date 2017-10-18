#pragma once


#include "SpriteRendererManager.h"
#include "AudioManager.h"


#include "GLHeaders.h"
#include "GameObject.h"
#define GL3_PROTOTYPES 1
#include "Scene.h"
class GameManager 
{
public:

    GameManager();
    void Update(int ticks);


private:
	

   GameManager();
   void BeginLoop(Scene* scene);
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