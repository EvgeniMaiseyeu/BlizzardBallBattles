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

void RunGame();
bool HandlePolledEvent(SDL_Event event);
bool ThrowBall = false;

GameManager* gameManager;
Player *chensPlayer1, *chensPlayer2, *snowBall1, *snowBall2; //Chens player object, to be refactored when possible

int main(int argc, char *argv[])
{
  gameManager = new GameManager();
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
  bool gameLoop = true;
  int lastTicks = SDL_GetTicks();

  //Sprites for testing d
  Shader ourShader(BuildPath("Game/Assets/Shaders/vertex_shader.vs").c_str(), BuildPath("Game/Assets/Shaders/fragment_shader.fs").c_str());
  GLuint texture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/Character.png"));
  GLuint texture2 = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/Character2.png"));
  GLuint snowTexture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/SnowTile.png"));
  GLuint iceTexture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/IceTile.png"));

  float width = getGameWidth();
  float height = getGameHeight();
  float leftBounding = getGameLeftX();
  float bottomBounding = getGameBottomY();

  //Setup Tiles
  for(int x = 0; x < width; x++) {
    GLuint textureToUse = snowTexture;
    if (x >= width * 0.4f && x <= width * 0.6f ) {
      textureToUse = iceTexture;
    }
    for(int y = 0; y < height; y++ ) {
      GameObject* tile = new GameObject();
      tile->AddComponent("SpriteRenderer", (Component*)new SpriteRenderer(tile));
      SpriteRenderer* spriteRenderer = (SpriteRenderer*)tile->GetComponent("SpriteRenderer");
      spriteRenderer->SetActiveTexture(textureToUse);
      spriteRenderer->SetActiveShader(&ourShader);
      ((Transform*)tile->GetComponent("Transform"))->setPosition(leftBounding + x + 0.5, bottomBounding + y + 0.5);
    }
  }

  //Setup spinning player     制作玩家和雪球在这里。。。。
  /*GameObject* player1 = new GameObject();
  player1->AddComponent("SpriteRenderer", (Component*)new SpriteRenderer(player1));
  SpriteRenderer* spriteRenderer = (SpriteRenderer*)player1->GetComponent("SpriteRenderer");
  spriteRenderer->SetActiveTexture(texture);
  spriteRenderer->SetActiveShader(&ourShader);
  Transform* transform = (Transform*)player1->GetComponent("Transform");
  transform->setPosition(10, 8);

  GameObject* player2 = new GameObject();
  player2->AddComponent("SpriteRenderer", (Component*)new SpriteRenderer(player2));
  spriteRenderer = (SpriteRenderer*)player2->GetComponent("SpriteRenderer");
  spriteRenderer->SetActiveTexture(texture);
  spriteRenderer->SetActiveShader(&ourShader);
  transform = (Transform*)player2->GetComponent("Transform");
  transform->setPosition(-5, 4);
  transform->setScale(2.0f);*/
  

  //fkfkfkfkfkfkfkfkfkCHENNNNNNNNNNNNNNNNNNNNNNNNNNNNN       玩家就是一个图片，雪球也可以用一样的代码弄。
  //GLuint texture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/Character.png"));
  chensPlayer1 = new Player(&ourShader, texture);
  Transform* transform = (Transform*)chensPlayer1->GetComponent("Transform");
  transform->setPosition(-7, 2);
  transform->setScale(3.0f);

  snowBall1 = new Player(&ourShader, iceTexture);
  transform = (Transform*)snowBall1->GetComponent("Transform");
  transform->setPosition(-7, 0);
  transform->setScale(1.0f);

  //GLuint texture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/Character2.png"));
  chensPlayer2 = new Player(&ourShader, texture2);
  transform = (Transform*)chensPlayer2->GetComponent("Transform");
  transform->setPosition(10, 2);
  transform->setScale(3.0f);

  snowBall2 = new Player(&ourShader, iceTexture);
  transform = (Transform*)snowBall2->GetComponent("Transform");
  transform->setPosition(10, 0);
  transform->setScale(1.0f);
  

  float timeDelta = 0.0f;

  while (gameLoop) {
    //Handle events like key pressed
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (!HandlePolledEvent(event)) {
        gameLoop = false;
      }
    }

    //Update game
    gameManager->Update(timeDelta);

    //Temporary place where we update GameObjects
    ((Transform*)snowBall1->GetComponent("Transform"))->addRotation(20.0f);
	((Transform*)snowBall2->GetComponent("Transform"))->addRotation(-20.0f);

    //Cap at MAX_FPS (60) FPS and delay the uneeded time
    int newTicks = SDL_GetTicks();
    int difference = newTicks - lastTicks;
    int delay = 1000 / MAX_FPS - difference;
    if (delay > 0) {
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

