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
#include "AI.h"

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
	}
}

void GameScene_Alpha_Networked::OnConnected() {
	float teamOneX = -7.5f;
	float teamTwoX = 7.5f;

	if (NetworkingManager::GetInstance()->IsHost()) {
		player1 = new Battler(1, "Character.png", "Player1", true);
		player1->GetTransform()->setX(teamOneX);
		player2 = new Battler(2, "Character.png", "Player2", false);
		player2->GetTransform()->setX(teamTwoX);
		player2->GetTransform()->setRotation(180.0f);
		player1->AddComponent<Sender*>(new Sender(player1, "Player1"));
		player2->AddComponent<Receiver*>(new Receiver(player2, "Player2"));
		player1->AddComponent<Player*>(new Player(player1, SDLK_a, SDLK_d, SDLK_w, SDLK_s, SDLK_SPACE));

		AI1T1 = new Battler(1, "Character.png", "AI1T1", true);
		AI1T1->GetTransform()->setPosition(teamOneX, 2.5f);
		AI1T1->AddComponent<AI*>(new AI(AI1T1));
		AI2T1 = new Battler(1, "Character.png", "AI2T1", true);
		AI2T1->GetTransform()->setPosition(teamOneX, -2.5f);
		AI2T1->AddComponent<AI*>(new AI(AI2T1));

		AI1T2 = new Battler(2, "Character.png", "AI1T2", false);
		AI1T2->GetTransform()->setPosition(teamTwoX, 2.5f);
		AI1T2->GetTransform()->setRotation(180.0f);
		AI1T2->AddComponent<AI*>(new AI(AI1T2));
		AI2T2 = new Battler(2, "Character.png", "AI2T2", false);
		AI2T2->GetTransform()->setPosition(teamTwoX, -2.5f);
		AI2T2->GetTransform()->setRotation(180.0f);
		AI2T2->AddComponent<AI*>(new AI(AI2T2));

		AI1T1->AddComponent<Sender*>(new Sender(AI1T1, "AI1T1"));
		AI2T1->AddComponent<Sender*>(new Sender(AI2T1, "AI2T1"));

		AI1T2->AddComponent<Receiver*>(new Receiver(AI1T2, "AI1T2"));
		AI2T2->AddComponent<Receiver*>(new Receiver(AI2T2, "AI2T2"));
	}
	else {
		player1 = new Battler(1, "Character.png", "Player1", false);
		player1->GetTransform()->setX(teamOneX);
		player2 = new Battler(2, "Character.png", "Player2", true);
		player2->GetTransform()->setX(teamTwoX);
		player2->GetTransform()->setRotation(180.0f);
		player1->AddComponent<Receiver*>(new Receiver(player1, "Player1"));
		player2->AddComponent<Sender*>(new Sender(player2, "Player2"));
		player2->AddComponent<Player*>(new Player(player2, SDLK_a, SDLK_d, SDLK_w, SDLK_s, SDLK_SPACE));

		AI1T1 = new Battler(1, "Character.png", "AI1T1", false);
		AI1T1->GetTransform()->setPosition(teamOneX, 2.5f);
		AI1T1->AddComponent<AI*>(new AI(AI1T1));
		AI2T1 = new Battler(1, "Character.png", "AI2T1", false);
		AI2T1->GetTransform()->setPosition(teamOneX, -2.5f);
		AI2T1->AddComponent<AI*>(new AI(AI2T1));

		AI1T2 = new Battler(2, "Character.png", "AI1T2", true);
		AI1T2->GetTransform()->setPosition(teamTwoX, 2.5f);
		AI1T2->GetTransform()->setRotation(180.0f);
		AI1T2->AddComponent<AI*>(new AI(AI1T2));
		AI2T2 = new Battler(2, "Character.png", "AI2T2", true);
		AI2T2->GetTransform()->setPosition(teamTwoX, -2.5f);
		AI2T2->GetTransform()->setRotation(180.0f);
		AI2T2->AddComponent<AI*>(new AI(AI2T2));

		AI1T1->AddComponent<Receiver*>(new Receiver(AI1T1, "AI1T1"));
		AI2T1->AddComponent<Receiver*>(new Receiver(AI2T1, "AI2T1"));

		AI1T2->AddComponent<Sender*>(new Sender(AI1T2, "AI1T2"));
		AI2T2->AddComponent<Sender*>(new Sender(AI2T2, "AI2T2"));
	}
	isConnected = true;
}