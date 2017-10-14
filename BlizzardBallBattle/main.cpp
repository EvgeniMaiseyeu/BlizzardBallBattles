//Using SDL and standard IO
#include "GLHeaders.h"
#define GL3_PROTOTYPES 1
#include <stdio.h>
#include <string>
#include <iostream>
#include "SharedConstants.h"
#include "Shader.h"
#include "Transform.h"
#include "HelperFunctions.h"
#include "GameManager.h" //Engine/Manager/GameManager.h
#include "SpriteRendererManager.h"
#include "GameObject.h"
#include "Player.h"
#include "ComponentTemplate.h"
#include "GameObjectTemplate.h"
#include "Vector2.h"
#include "InputManager.h"
#include "MessageManager.h"

void RunGame();
bool HandlePolledEvent(SDL_Event event);
bool ThrowBall = false;
float timeDelta = 0;

GameManager* gameManager;
Player *chensPlayer1, *chensPlayer2, *snowBall1, *snowBall2; //Chens player object, to be refactored when possible

int main(int argc, char *argv[])
{
   if (!SpriteRendererManager::GetInstance()->Init()) {
   	return -1;
   }
  gameManager = new GameManager();
  RunGame();
  SpriteRendererManager::GetInstance()->Cleanup();
  delete(SpriteRendererManager::GetInstance());

  return 0;
}

void RunGame()
{
	bool gameLoop = true;
	int lastTicks = SDL_GetTicks();
  
	while (gameLoop) 
	{
		//Handle events like key pressed
		InputManager::GetInstance()->UpdateKeys();
		SDL_Event event;
		while (SDL_PollEvent(&event)) 
		{
			InputManager::GetInstance()->HandlePolledEvent(event);
			if (!HandlePolledEvent(event)) 
			{
				gameLoop = false;
			}
		}
		gameManager->Update(timeDelta);
		//chensPlayer1->Update(timeDelta);
		//chensPlayer2->Update(timeDelta);
		//snowBall1->Update(timeDelta);
		//snowBall2->Update(timeDelta);
		//Cap at MAX_FPS (60) FPS and delay the uneeded time
		int newTicks = SDL_GetTicks();
		int difference = newTicks - lastTicks;
		int delay = 1000 / MAX_FPS - difference;
		if (delay > 0) 
		{
			SDL_Delay(delay);
		}
		timeDelta = newTicks - lastTicks;
		lastTicks = newTicks;
	  }
}

bool HandlePolledEvent(SDL_Event event) {
  bool continueGameLoop = true;

  if (event.type == SDL_QUIT)
    continueGameLoop = false;

  //KeyDown is actually KeyHeld, with SDL_KEYUP being on release.
  //Need state machine to keeep track of proper Pressed/Held/Release states, this event could update them
  

  if (event.type == SDL_KEYDOWN)
  {
    switch (event.key.keysym.sym)
    {
    case SDLK_ESCAPE:
      continueGameLoop = false;
      break;
    case SDLK_w: //When W is pressed   这里是怎样移动玩家
		chensPlayer1->PressedUp();
		snowBall1->PressedUp();
      break;
    case SDLK_a: //When A is pressed
		chensPlayer1->PressedLeft();
		snowBall1->PressedLeft();
      break;
    case SDLK_s:
		chensPlayer1->PressedDown();
		snowBall1->PressedDown();
      break;
	case SDLK_d:
		chensPlayer1->PressedRight();
		snowBall1->PressedRight();
		break;
	case SDLK_i: //When W is pressed   这里是怎样移动玩家
		chensPlayer2->PressedUp();
		snowBall2->PressedUp();
		break;
	case SDLK_j: //When A is pressed
		chensPlayer2->PressedLeft();
		snowBall2->PressedLeft();
		break;
	case SDLK_k:
		chensPlayer2->PressedDown();
		snowBall2->PressedDown();
		break;
	case SDLK_l:
		chensPlayer2->PressedRight();
		snowBall2->PressedRight();
		break;
    default:
      break;
    }
  }
  
  return continueGameLoop;
}

