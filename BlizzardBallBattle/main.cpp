//Using SDL and standard IO
#include <stdio.h>
#include <string>
#include <iostream>
#include "GameManager.h"
#include "SpriteRendererManager.h"
#include "MatchManager.h"
#include "Scenes.h"

void RunGame();

int main(int argc, char *argv[])
{
  if (!SpriteRendererManager::GetInstance()->Init()) {
    return -1;
  }
  RunGame();
  SpriteRendererManager::GetInstance()->Cleanup();
  delete(SpriteRendererManager::GetInstance());

  return 0;
}

void RunGame()
{
  GameManager::GetInstance();
  SpriteRendererManager::GetInstance();

  NetworkingTestScene* testScene = new NetworkingTestScene();
  testScene->OnStart();
  //PlayerTestScene* testScene = new PlayerTestScene();
  //testScene->OnStart();
  //
  GameManager::GetInstance()->BeginLoop(testScene);
}
