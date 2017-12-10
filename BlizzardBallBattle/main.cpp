//Using SDL and standard IO
#include <stdio.h>
#include <string>
#include <iostream>
#include "GameManager.h"
#include "SpriteRendererManager.h"
#include "Scenes.h"
#include "NetworkingManager.h"

void RunGame();

int main(int argc, char *argv[])
{
  if (!SpriteRendererManager::GetInstance()->Init()) {
    return -1;
  }
  //For Visual Studio std::cout outputs
	#if defined _WIN32 || defined _WIN64
	  AllocConsole ();
	  freopen ("CONOUT$", "w", stdout);
	  freopen ("CONOUT$", "w", stderr);
	#endif

  //TODO, not handle this in command line
  if (argc > 1) {
    NetworkingManager::GetInstance()->SetIP(argv[1]);
    if (argc > 2)
    NetworkingManager::GetInstance()->SetIP(argv[1], atoi(argv[2]));
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
  GameManager::GetInstance()->OnStart();
}
