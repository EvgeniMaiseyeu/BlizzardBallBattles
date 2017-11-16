#include "SceneTemplate.h"
#include "MatchManager.h"
#include "GLHeaders.h"
#include "SpriteRendererManager.h"
#include "Shader.h"
#include "SharedConstants.h"
#include "Sender.h"
#include "Receiver.h"
#include "SpriteSheet.h"
#include <iostream>

void SceneTemplate::OnStart(){
	BuildBaseScene();
	GLuint snowTexture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/SnowTile.png"));
	GLuint iceTexture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/IceTile.png"));
	GLuint characterTexture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/Character.png"));
	GLuint spriteSheetTexture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/WalkingSpriteSheet.png"));

	// Create Players
	MatchManager::GetInstance()->CreateBattlers(Shader::GetShader(), characterTexture, spriteSheetTexture, true, true);
}

void SceneTemplate::OnEnd() {
	//delete(player1);
	//delete(player2);
}

void SceneTemplate::OnUpdate(int ticks) {
	//player1->GetComponent<Sender*>()->SendUpdate();
	//NetworkingManagerTemp::GetInstance()->SendQueuedEvents();
}