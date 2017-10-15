#include "NetworkingTestScene.h"
#include "GLHeaders.h"
#include "SpriteRendererManager.h"
#include "Shader.h"
#include "HelperFunctions.h"
#include "SharedConstants.h"
#include "Sprite.h"
#include "SpriteRenderer.h"
#include "Transform.h"
#include "Sender.h"
#include "Receiver.h"
#include "UserDefinedRenderLayers.h"
#include "SpriteSheet.h"
#include <iostream>

void NetworkingTestScene::OnStart() {
    std::cout << "Starting NetworkingTestScene Setup" << std::endl;
    ourShader = new Shader(BuildPath("Game/Assets/Shaders/vertex_shader.vs").c_str(), BuildPath("Game/Assets/Shaders/voxel.fs").c_str());
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
        spriteRenderer->SetActiveSprite((ISprite*)new Sprite(textureToUse));
        spriteRenderer->SetActiveShader(ourShader);
        spriteRenderer->SetLayer(RENDER_LAYER_BACKGROUND);
        tile->GetComponent<Transform*>()->setPosition(leftBounding + x + 0.5, bottomBounding + y + 0.5, -1.0f);
      }
    }

    GLuint spriteSheetTexture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/WalkingSpriteSheet.png"));
    player1 = new GameObject();
    player1->AddComponent<SpriteRenderer*>(new SpriteRenderer(player1));
    player1->AddComponent<Sender*>(new Sender(player1, "Player"));
    SpriteRenderer* spriteRenderer = player1->GetComponent<SpriteRenderer*>();
    spriteRenderer->SetActiveSprite((ISprite*)new SpriteSheet(spriteSheetTexture, 5, 3, 1));
    spriteRenderer->SetActiveShader(ourShader);
    player1->GetComponent<Transform*>()->setRotation(-90.0f); //My spritesheet is 90 degrees off
    player1->GetComponent<Transform*>()->setScale(10.0f);
  
    player2 = new GameObject();
    player2->AddComponent<SpriteRenderer*>(new SpriteRenderer(player2));
    player2->AddComponent<Receiver*>(new Receiver(player2, "Player"));
    spriteRenderer = player2->GetComponent<SpriteRenderer*>();
    spriteRenderer->SetActiveSprite((ISprite*)new SpriteSheet(spriteSheetTexture, 5, 3, 1));
    spriteRenderer->SetActiveShader(ourShader);
    std::cout << "Ending NetworkingTestScene Setup" << std::endl;
}

void NetworkingTestScene::OnEnd() {
    delete(player1);
    delete(player2);
}

void NetworkingTestScene::OnUpdate() {
    player1->GetComponent<Sender*>()->SendUpdate();
    NetworkingManagerTemp::GetInstance()->SendQueuedEvents();
}