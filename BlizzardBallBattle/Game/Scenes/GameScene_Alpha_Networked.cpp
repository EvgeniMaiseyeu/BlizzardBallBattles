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
#include <vector>
#include "MatchManager.h"
#include "Collider.h"

GameScene_Alpha_Networked::GameScene_Alpha_Networked(int p1ai, int p2ai) : GameScene(p1ai, p2ai) {
	this->p1ai = p1ai;
	this->p2ai = p2ai;
}

void GameScene_Alpha_Networked::OnStart() {
	isConnected = false;
}

void GameScene_Alpha_Networked::OnEnd() {
	//delete(player1);
	//delete(player2);
	//Purge ();
}

void GameScene_Alpha_Networked::OnPause () {
	MatchManager::GetInstance ()->Stop ();
	NetworkingManager::GetInstance ()->Close ();
	ClearScene ();
}

void GameScene_Alpha_Networked::OnUpdate(int ticks) {
	if (!isConnected && NetworkingManager::GetInstance()->IsConnected()) {
		OnConnected();
	}
}

void GameScene_Alpha_Networked::OnConnected() {
	BuildBaseScene ();

	GLuint snowTexture = SpriteRendererManager::GetInstance ()->GenerateTexture (BuildPath ("Game/Assets/Sprites/SnowTile.png"));
	GLuint iceTexture = SpriteRendererManager::GetInstance ()->GenerateTexture (BuildPath ("Game/Assets/Sprites/IceTile.png"));
	GLuint characterTexture = SpriteRendererManager::GetInstance ()->GenerateTexture (BuildPath ("Game/Assets/Sprites/Character.png"));
	GLuint spriteSheetTexture = SpriteRendererManager::GetInstance ()->GenerateTexture (BuildPath ("Game/Assets/Sprites/WalkingSpriteSheet.png"));

	if (NetworkingManager::GetInstance()->IsHost()) {
		p1ai = 4;
		p2ai = 5;
	}
	else {
		p1ai = 5;
		p2ai = 4;
	}
	MatchManager::GetInstance ()->CreateBattlers (Shader::GetShader (), characterTexture, spriteSheetTexture, p1ai, p2ai);
	isConnected = true;
}