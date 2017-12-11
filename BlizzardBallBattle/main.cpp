//Using SDL and standard IO
#include <stdio.h>
#include <string>
#include <iostream>
#include "GameManager.h"
#include "SpriteRendererManager.h"
#include "GameObject.h"
#include "AudioManager.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include "Scenes.h"
#include "NetworkingManager.h"



void RunGame();

int main(int argc, char *argv[])
{
	//For Visual Studio std::cout outputs
#if defined _WIN32 || defined _WIN64
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
#endif

  //AudioManager audioManager;
  //audioManager.PlaySoundEffect("mario_.mp3");
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
  if (argc < 2) {
	  std::cout << "Networking Join Directed to IP " << DEFAULT_IP << ":" << DEFAULT_PORT << std::endl;
  }
  if (argc > 1) {
	  NetworkingManager::GetInstance ()->SetIP (argv[1]);
	  std::cout << "Networking Join Directed to IP " << argv[1] << ":" << DEFAULT_PORT << std::endl;
	  if (argc > 2) {
		  NetworkingManager::GetInstance ()->SetIP (argv[1], atoi (argv[2]));
		  std::cout << "Networking Join Directed to IP " << argv[1] << ":" << argv[2] << std::endl;
	  }
  }

  RunGame ();
  SpriteRendererManager::GetInstance ()->Cleanup ();
  delete(SpriteRendererManager::GetInstance ());

	return 0;
}

void RunGame()
{
  GameManager::GetInstance();
  SpriteRendererManager::GetInstance();
  //GameManager::GetInstance()->BeginLoop(new SceneTemplate());
  GameManager::GetInstance()->OnStart();
}
