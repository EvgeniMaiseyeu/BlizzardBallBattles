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
#include "ComponentTemplate.h"
#include "GameObjectTemplate.h"
#include "InputManager.h"
#include "MessageManager.h"

void RunGame();
bool HandlePolledEvent(SDL_Event event);

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
  //put this in gamemanager beginloop
    SpriteRendererManager::GetInstance();
    MatchManager::GetInstance()->StartGame();

  //Sprites for testing d
  Shader ourShader(BuildPath("Game/Assets/Shaders/vertex_shader.vs").c_str(), BuildPath("Game/Assets/Shaders/fragment_shader.fs").c_str());
  GLuint texture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/Character.png"));
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
      tile->AddComponent<SpriteRenderer*>(new SpriteRenderer(tile));
      SpriteRenderer* spriteRenderer = tile->GetComponent<SpriteRenderer*>();
      spriteRenderer->SetActiveTexture(textureToUse);
      spriteRenderer->SetActiveShader(&ourShader);
      tile->GetComponent<Transform*>()->setPosition(leftBounding + x + 0.5, bottomBounding + y + 0.5);
    }
  }

  //Setup spinning player
  GameObject* player1 = new GameObject();
  player1->AddComponent<SpriteRenderer*>(new SpriteRenderer(player1));
  SpriteRenderer* spriteRenderer = player1->GetComponent<SpriteRenderer*>();
  spriteRenderer->SetActiveTexture(texture);
  spriteRenderer->SetActiveShader(&ourShader);

  //###TEMPLATE OBJECT EXAMPLE###//
  //Create it, who's constructor adds ComponentTemplate
  GameObjectTemplate* gameObjectTemplate = new GameObjectTemplate();
  //Now calling it's method, which calls ComponentTemplates ExampleMethod too
  gameObjectTemplate->ExampleMethod();

  float timeDelta = 0.0f;

  //MESSAGING EXAMPLE
  //subscribe a function to the event "test", store the unique id for this event for later removal.
  int id = MessageManager::Subscribe("test", [](std::map<std::string, void*> data) -> void {

    //converting a void* to its respective std::string*. Do it this way if its not a primitive type.
    std::string *str = static_cast<std::string *>(data["somedata"]);

    //converting a void* to its respective int*, do it this way if its primitive data type.
    int *in = (int *)(&data["someint"]);

    //printing out the data we got from the data.
    std::cout << *in << " " << *str << std::endl;
  });

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
}