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
#include "Sprite.h"
#include "SpriteSheet.h"
#include "InputManager.h"
#include "MessageManager.h"
#include "Sender.h"
#include "Receiver.h"
#include "NetworkingManagerTemp.h"
#include "UserDefinedRenderLayers.h"

void RunGame();
bool HandlePolledEvent(SDL_Event event);
bool ThrowBall = false;

Player *chensPlayer1, *chensPlayer2, *snowBall1, *snowBall2; //Chens player object, to be refactored when possible

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
  bool gameLoop = true;
  int lastTicks = SDL_GetTicks();

  //Sprites for testing d
  Shader ourShader(BuildPath("Game/Assets/Shaders/vertex_shader.vs").c_str(), BuildPath("Game/Assets/Shaders/fragment_shader.fs").c_str());
  GLuint iceTexture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/IceTile.png"));

  GLuint texture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/Character.png"));
  GLuint texture2 = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/Character2.png"));
  GLuint snowTexture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/SnowTile.png"));

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
      tile->AddComponent<SpriteRenderer*>(new SpriteRenderer(tile));
      SpriteRenderer* spriteRenderer = tile->GetComponent<SpriteRenderer*>();
      spriteRenderer->SetActiveSprite((ISprite*)new Sprite(textureToUse));
      spriteRenderer->SetActiveShader(&ourShader);
      spriteRenderer->SetLayer(RENDER_LAYER_BACKGROUND);
      tile->GetComponent<Transform*>()->setPosition(leftBounding + x + 0.5, bottomBounding + y + 0.5, -1.0f);
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
  /*chensPlayer1 = new Player(&ourShader, texture);
  Transform* transform = (Transform*)chensPlayer1->GetComponent<Transform*>();
  transform->setPosition(-7, 2);
  InputManager* inputManager = InputManager::GetInstance();
  transform->setScale(3.0f);

  snowBall1 = new Player(&ourShader, iceTexture);
  transform = (Transform*)snowBall1->GetComponent<Transform*>();
  transform->setPosition(-7, 0);
  inputManager = InputManager::GetInstance();
  transform->setScale(1.0f);

  //GLuint texture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/Character2.png"));
  chensPlayer2 = new Player(&ourShader, texture2);
  transform = (Transform*)chensPlayer2->GetComponent<Transform*>();
  transform->setPosition(10, 2);
  inputManager = InputManager::GetInstance();
  transform->setScale(3.0f);

  snowBall2 = new Player(&ourShader, iceTexture);
  transform = (Transform*)snowBall2->GetComponent<Transform*>();
  transform->setPosition(10, 0);
  inputManager = InputManager::GetInstance();
  transform->setScale(1.0f);*/
  //SpriteRendererManager::GetInstance()->DisableRenderingLayer(RENDER_LAYER_DEFAULT);

  //Setup spinning player
  GLuint spriteSheetTexture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/WalkingSpriteSheet.png"));
  GameObject* player1 = new GameObject();
  player1->AddComponent<SpriteRenderer*>(new SpriteRenderer(player1));
  player1->AddComponent<Sender*>(new Sender(player1, "Player"));
  SpriteRenderer* spriteRenderer = player1->GetComponent<SpriteRenderer*>();
  spriteRenderer->SetActiveSprite((ISprite*)new SpriteSheet(spriteSheetTexture, 5, 3, 1));
  spriteRenderer->SetActiveShader(&ourShader);
  player1->GetComponent<Transform*>()->setRotation(-90.0f); //My spritesheet is 90 degrees off
  player1->GetComponent<Transform*>()->setScale(10.0f);

  GameObject* player2 = new GameObject();
  player2->AddComponent<SpriteRenderer*>(new SpriteRenderer(player2));
  player2->AddComponent<Receiver*>(new Receiver(player2, "Player"));
  spriteRenderer = player2->GetComponent<SpriteRenderer*>();
  spriteRenderer->SetActiveSprite((ISprite*)new SpriteSheet(spriteSheetTexture, 5, 3, 1));
  spriteRenderer->SetActiveShader(&ourShader);
  

  //###TEMPLATE OBJECT EXAMPLE###//
  //Create it, who's constructor adds ComponentTemplate
  GameObjectTemplate* gameObjectTemplate = new GameObjectTemplate();
  //Now calling it's method, which calls ComponentTemplates ExampleMethobd too
  gameObjectTemplate->ExampleMethod();

  float timeDelta = 0.0f;
  int frameSkipper = 0;

  //MESSAGING EXAMPLE
  //subscribe a function to the event "test", store the unique id for this event for later removal.
  int id = MessageManager::Subscribe("test", [](std::map<std::string, void*> data) -> void {

    //converting a void* to its respective std::string*. Do it this way if its not a primitive type.
    std::string *str = static_cast<std::string *>(data["somedata"]);

    //converting a void* to its respective int*, do it this way if its primitive data type.
    int *in = (int *)(&data["someint"]);

    //printing out the data we got from the data.
    std::cout << *in << " " << *str << std::endl;
  }, (void*)0);

  //create data map to pass into the callback, notice how the data is pointers.
  std::map<std::string, void*> data;
  std::string* s = new std::string("AMAZING");
  data["somedata"] = s;
  data["someint"] = (int *)44;

  //send the event.
  MessageManager::SendEvent("test", data);

  //unsubscribe the listener from the event.
  MessageManager::UnSubscribe("test", id);

  //send the event again. No listeners for this event so nothing happens.
  MessageManager::SendEvent("test", data);

  
  //MESSAGING EXAMPLE END
  GameManager::GetInstance()->BeginLoop();

    //Update game   把那些sdl w 的控制方法从最底部移到这里
    //gameManager->Update(timeDelta);
    //player1->GetComponent<Sender*>()->SendUpdate();
    //std::cout << "PLAYER 1::ACTUAL X :" << player1->GetComponent<Transform*>()->getX() << "::ACTUAL ROTATION : " << player1->GetComponent<Transform*>()->getRotation() << std::endl;
    //std::cout << "PLAYER 2::ACTUAL X :" << player2->GetComponent<Transform*>()->getX() << "::ACTUAL ROTATION : " << player2->GetComponent<Transform*>()->getRotation() << std::endl;
    
    //NetworkingManagerTemp::GetInstance()->SendQueuedEvents();

    //std::cout << "ACTUALLY DONE!!!!!!!!" << std::endl;
    //Temporary place where we update GameObjects
    /*if (frameSkipper++ % (MAX_FPS / 4) == 0) {
      player1->GetComponent<Transform*>()->addRotation(0.5f);
      SpriteSheet* spriteSheet = (SpriteSheet*)player1->GetComponent<SpriteRenderer*>()->GetSprite();
      spriteSheet->NextIndex();
    }*/

    //Cap at MAX_FPS (60) FPS and delay the uneeded time
  //}
}
