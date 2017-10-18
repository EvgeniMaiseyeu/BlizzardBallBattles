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
  gameManager = new GameManager();
  //AudioManager audioManager;
  //audioManager.PlaySoundEffect("mario_.mp3");
  if (!SpriteRendererManager::GetInstance()->Init()) {
    return -1;
  }

  /*SDL_AudioInit;
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
	  std::cout << "ERROR: " << Mix_GetError() << std::endl;
	  return false;
  }

  Mix_Music *bgm = Mix_LoadMUS("mario_.wav");
  Mix_Chunk *soundEffect = Mix_LoadWAV("");

  bool isRunning = true;
  SDL_Event ev;
  while (isRunning) {
	  while (SDL_PollEvent(&ev) != 0) {
		  if (ev.type == SDLK_AUDIOPLAY) {
			  switch (ev.key.keysym.sym) {
			 // case SDLK_p:
				  if (!Mix_PlayingMusic())
					  Mix_PlayMusic(bgm, -1);
				  else if (Mix_PausedMusic())
					  Mix_ResumeMusic();
				  else
					  Mix_PauseMusic();
				  break;
			/*  case SDLK_s:
				  Mix_HaltMusic();
				  break; 
			  }

		  }
	  }
  }


  Mix_FreeChunk(soundEffect);
  Mix_FreeMusic(bgm);

  bgm = nullptr;
  soundEffect = nullptr;
  Mix_Quit();
  return 0; */


 /* if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
	  std::cout << SDL_GetError() << std::endl;
	  return 1;
  }

 
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
  Mix_Music *sound = Mix_LoadMUS("mario_.wav");
  Mix_PlayMusic(sound, 1);
  SDL_Delay(10000);    
  return 0; */

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
  //GameManager::GetInstance()->BeginLoop(new SceneTemplate());
  GameManager::GetInstance()->BeginLoop(new AudioTestScene());
}
