#include "NetworkingTestScene.h"
#include "SpriteRendererManager.h"
#include "HelperFunctions.h"
#include "SharedConstants.h"
#include "Sprite.h"
#include "SpriteRenderer.h"
#include "Transform.h"
#include "Sender.h"
#include "Receiver.h"
#include "NetworkingManager.h"
#include <iostream>
#include "Player.h"
#include "Battler.h"
#include "GLHeaders.h"
#include "InputManager.h"

void NetworkingTestScene::OnStart() {
    ourShader = new Shader(BuildPath("Game/Assets/Shaders/vertex_shader.vs").c_str(), BuildPath("Game/Assets/Shaders/fragment_shader.fs").c_str());
    GLuint texture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/Character.png"));

    player1 = new GameObject();
    player1->AddComponent<SpriteRenderer*>(new SpriteRenderer(player1));
    player1->AddComponent<Sender*>(new Sender(player1, "Player1"));
    SpriteRenderer* spriteRenderer = player1->GetComponent<SpriteRenderer*>();
    spriteRenderer->SetActiveSprite((ISprite*)new Sprite(texture));
    spriteRenderer->SetActiveShader(ourShader);
  
    player2 = new GameObject();
    player2->AddComponent<SpriteRenderer*>(new SpriteRenderer(player2));
    player2->AddComponent<Receiver*>(new Receiver(player2, "Player2"));
    spriteRenderer = player2->GetComponent<SpriteRenderer*>();
	spriteRenderer->SetActiveSprite((ISprite*)new Sprite(texture));
    spriteRenderer->SetActiveShader(ourShader);

	//Never touched the transform of player2, but it rotates/scales with player1 through the NetworkingManager
}

void NetworkingTestScene::OnEnd() {
    delete(player1);
    delete(player2);
}

void NetworkingTestScene::OnUpdate() {
    if (InputManager::GetInstance()->onKey(SDLK_a)) {
        player1->GetComponent<Transform*>()->addX(-0.1f);
        player1->GetComponent<Transform*>()->setRotation(180);
    }
    if (InputManager::GetInstance()->onKey(SDLK_d)) {
        player1->GetComponent<Transform*>()->addX(0.1f);
        player1->GetComponent<Transform*>()->setRotation(0);
    }
    if (InputManager::GetInstance()->onKey(SDLK_s)) {
        player1->GetComponent<Transform*>()->addY(-0.1f);
        player1->GetComponent<Transform*>()->setRotation(90);
    }
    if (InputManager::GetInstance()->onKey(SDLK_w)) {
        player1->GetComponent<Transform*>()->addY(0.1f);
        player1->GetComponent<Transform*>()->setRotation(-90);
    }
}