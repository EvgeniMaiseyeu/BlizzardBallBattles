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
#include "Player.h"

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
			player1->AddComponent<Player*>(new Player(player1, SDLK_a, SDLK_d, SDLK_w, SDLK_s, SDLK_SPACE));
		}
		else {
			player1->AddComponent<Receiver*>(new Receiver(player1, "Player1"));
			player2->AddComponent<Sender*>(new Sender(player2, "Player2"));
			player2->AddComponent<Player*>(new Player(player2, SDLK_a, SDLK_d, SDLK_w, SDLK_s, SDLK_SPACE));
		}
		isConnected = true;
	}
}

void GameScene_Alpha_Networked::OnConnected() {
	player1 = new Battler(1, "Character.png");
	player1->GetTransform()->setX(-7.5f);

	player2 = new Battler(2, "Character.png");
	player2->GetTransform()->setX(7.5f);
	player2->GetTransform()->setRotation(180.0f);
}