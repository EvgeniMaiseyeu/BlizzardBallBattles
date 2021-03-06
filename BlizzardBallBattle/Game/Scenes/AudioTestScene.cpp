#include "AudioTestScene.h"
#include "MatchManager.h"
#include "GLHeaders.h"
#include "SpriteRendererManager.h"
#include "Shader.h"
#include "SharedConstants.h"
#include "Sender.h"
#include "Receiver.h"
#include "SpriteSheet.h"
#include <iostream>
#include "GameObject.h"
#include "InputManager.h"
#include "AudioManager.h"

void AudioTestScene::OnStart() {
	ourShader = new Shader(BuildPath("Game/Assets/Shaders/vertex_shader.vs").c_str(), BuildPath("Game/Assets/Shaders/voxel.fs").c_str());
	GLuint snowTexture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/SnowTile.png"));
	GLuint iceTexture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/IceTile.png"));
	GLuint characterTexture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/Character.png"));
	GLuint spriteSheetTexture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/WalkingSpriteSheet.png"));

	// Create Map
	MatchManager::GetInstance()->CreateMap(ourShader, snowTexture, iceTexture);

	// Create Players
	MatchManager::GetInstance()->CreateBattlers(ourShader, characterTexture, spriteSheetTexture);


	
	
}

void AudioTestScene::OnEnd() {
	//delete(player1);
	//delete(player2);
}

void AudioTestScene::OnUpdate(int ticks) {
	if (InputManager::GetInstance()->onKeyPressed(SDLK_0)) {
		AudioManager::GetInstance()->PlayMusic("mario_.wav");
	}

	//player1->GetComponent<Sender*>()->SendUpdate();
	//NetworkingManagerTemp::GetInstance()->SendQueuedEvents();
}