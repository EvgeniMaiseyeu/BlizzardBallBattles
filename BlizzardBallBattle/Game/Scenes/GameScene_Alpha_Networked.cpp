#include "GameScene_Alpha_Networked.h"
#include "SpriteRendererManager.h"
#include "Shader.h"
#include "HelperFunctions.h"
#include "SharedConstants.h"
#include "SpriteRenderer.h"
#include "UserDefinedRenderLayers.h"
#include "SpriteSheet.h"
#include <iostream>
#include "HelperFunctions.h"
#include "GLHeaders.h"
#include "NetworkingManager.h"
#include "InputManager.h"
#include "Sender.h"
#include "Receiver.h"

void GameScene_Alpha_Networked::OnStart() {
	isConnected = false;
	BuildBaseScene();
}

void GameScene_Alpha_Networked::OnEnd() {
	delete(player1);
	delete(player2);
}

void GameScene_Alpha_Networked::OnUpdate(int ticks) {
	if (!isConnected && NetworkingManager::GetInstance()->IsConnected()) {
		OnConnected();
		if (NetworkingManager::GetInstance()->IsHost()) {
			player1->AddComponent<Sender*>(new Sender(player1, "Player1"));
			player2->AddComponent<Receiver*>(new Receiver(player2, "Player2"));
		}
		else {
			player1->AddComponent<Receiver*>(new Receiver(player1, "Player1"));
			player2->AddComponent<Sender*>(new Sender(player2, "Player2"));
		}
		isConnected = true;
	}

	if (isConnected) {
		GameObject* player = NetworkingManager::GetInstance()->IsHost() ? player1 : player2;
		//TODO: Replace onKey calls with player->AddComponent<ChensPlayer*>()
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

void GameScene_Alpha_Networked::OnConnected() {
	ourShader = new Shader(BuildPath("Game/Assets/Shaders/vertex_shader.vs").c_str(), BuildPath("Game/Assets/Shaders/fragment_shader.fs").c_str());
	GLuint spriteSheetTexture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/CharacterSheet.png"));
	player1 = new GameObject(false);
	player1->AddComponent<SpriteRenderer*>(new SpriteRenderer(player1));
	SpriteRenderer* spriteRenderer = player1->GetComponent<SpriteRenderer*>();
	spriteRenderer->SetActiveSprite((ISprite*)new SpriteSheet(spriteSheetTexture, 8, 2, 0));
	spriteRenderer->SetActiveShader(ourShader);
	player1->GetComponent<Transform*>()->setX(-7.5f);


	player2 = new GameObject(false);
	player2->AddComponent<SpriteRenderer*>(new SpriteRenderer(player2));
	spriteRenderer = player2->GetComponent<SpriteRenderer*>();
	spriteRenderer->SetActiveSprite((ISprite*)new SpriteSheet(spriteSheetTexture, 8, 2, 0));
	spriteRenderer->SetActiveShader(ourShader);
	player2->GetComponent<Transform*>()->setX(7.5f);
}