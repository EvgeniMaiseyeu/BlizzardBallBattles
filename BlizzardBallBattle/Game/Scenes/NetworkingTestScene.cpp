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

void NetworkingTestScene::OnStart() {
    ourShader = new Shader(BuildPath("Game/Assets/Shaders/vertex_shader.vs").c_str(), BuildPath("Game/Assets/Shaders/fragment_shader.fs").c_str());
    GLuint texture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/Character.png"));

    player1 = new GameObject();
    player1->AddComponent<SpriteRenderer*>(new SpriteRenderer(player1));
    player1->AddComponent<Sender*>(new Sender(player1, "Player"));
    SpriteRenderer* spriteRenderer = player1->GetComponent<SpriteRenderer*>();
    spriteRenderer->SetActiveSprite((ISprite*)new Sprite(texture));
    spriteRenderer->SetActiveShader(ourShader);
    player1->GetComponent<Transform*>()->setScale(5.0f);
  
    player2 = new GameObject();
    player2->AddComponent<SpriteRenderer*>(new SpriteRenderer(player2));
    player2->AddComponent<Receiver*>(new Receiver(player2, "Player"));
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
	player1->GetComponent<Transform*>()->addRotation(1);
    player1->GetComponent<Sender*>()->SendUpdate();
    NetworkingManager::GetInstance()->SendQueuedEvents();
}