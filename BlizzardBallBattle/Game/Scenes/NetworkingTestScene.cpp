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
    isConnected = false;

	//Never touched the transform of player2, but it rotates/scales with player1 through the NetworkingManager
}

void NetworkingTestScene::OnEnd() {
    delete(player1);
    delete(player2);
}

void NetworkingTestScene::OnUpdate() {
    if (!isConnected && NetworkingManager::GetInstance()->IsConnected()) {
        OnConnected();
        if (NetworkingManager::GetInstance()->IsHost()) {
            player1->AddComponent<Sender*>(new Sender(player1, "Player1"));
            player2->AddComponent<Receiver*>(new Receiver(player2, "Player2"));
        } else {
            player1->AddComponent<Receiver*>(new Receiver(player1, "Player1"));
            player2->AddComponent<Sender*>(new Sender(player2, "Player2"));
        }
        isConnected = true;
    }

    if (isConnected) {
        GameObject* player = NetworkingManager::GetInstance()->IsHost() ? player1 : player2;
        if (InputManager::GetInstance()->onKey(SDLK_a)) {
            player->GetComponent<Transform*>()->addX(-0.1f);
            player->GetComponent<Transform*>()->setRotation(180);
        }
        if (InputManager::GetInstance()->onKey(SDLK_d)) {
            player->GetComponent<Transform*>()->addX(0.1f);
            player->GetComponent<Transform*>()->setRotation(0);
        }
        if (InputManager::GetInstance()->onKey(SDLK_s)) {
            player->GetComponent<Transform*>()->addY(-0.1f);
            player->GetComponent<Transform*>()->setRotation(90);
        }
        if (InputManager::GetInstance()->onKey(SDLK_w)) {
            player->GetComponent<Transform*>()->addY(0.1f);
            player->GetComponent<Transform*>()->setRotation(-90);
        }
    }
}

void NetworkingTestScene::OnConnected() {
    ourShader = new Shader(BuildPath("Game/Assets/Shaders/vertex_shader.vs").c_str(), BuildPath("Game/Assets/Shaders/fragment_shader.fs").c_str());
    GLuint texture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/Character.png"));

    player1 = new GameObject(false);
    player1->AddComponent<SpriteRenderer*>(new SpriteRenderer(player1));
    SpriteRenderer* spriteRenderer = player1->GetComponent<SpriteRenderer*>();
    spriteRenderer->SetActiveSprite((ISprite*)new Sprite(texture));
    spriteRenderer->SetActiveShader(ourShader);
  
    player2 = new GameObject(false);
    player2->AddComponent<SpriteRenderer*>(new SpriteRenderer(player2));
    spriteRenderer = player2->GetComponent<SpriteRenderer*>();
	spriteRenderer->SetActiveSprite((ISprite*)new Sprite(texture));
    spriteRenderer->SetActiveShader(ourShader);
}