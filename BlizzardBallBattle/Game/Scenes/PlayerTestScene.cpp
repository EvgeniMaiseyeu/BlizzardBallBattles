#include "PlayerTestScene.h"
#include "SpriteRendererManager.h"
#include "Shader.h"
#include "HelperFunctions.h"
#include "SharedConstants.h"
#include "Sprite.h"
#include "SpriteRenderer.h"
#include "Transform.h"
#include "UserDefinedRenderLayers.h"
#include "InputManager.h"
#include "Player.h"
#include <iostream>

void PlayerTestScene::OnStart() {
	std::cout << "Starting NetworkingTestScene Setup" << std::endl;
	ourShader = new Shader(BuildPath("Game/Assets/Shaders/vertex_shader.vs").c_str(), BuildPath("Game/Assets/Shaders/fragment_shader.fs").c_str());
	GLuint texture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/Character.png"));
	GLuint texture2 = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/Character2.png"));
	GLuint snowTexture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/SnowTile.png"));
	GLuint iceTexture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/IceTile.png"));

	float width = getGameWidth();
	float height = getGameHeight();
	float leftBounding = getGameLeftX();
	float bottomBounding = getGameBottomY();

	//Setup Tiles
	for (int x = 0; x < width; x++) {
		GLuint textureToUse = snowTexture;
		if (x >= width * 0.4f && x <= width * 0.6f) {
			textureToUse = iceTexture;
		}
		for (int y = 0; y < height; y++) {
			GameObject* tile = new GameObject(false);
			tile->AddComponent<SpriteRenderer*>(new SpriteRenderer(tile));
			SpriteRenderer* spriteRenderer = tile->GetComponent<SpriteRenderer*>();
			spriteRenderer->SetActiveSprite((ISprite*)new Sprite(textureToUse));
			spriteRenderer->SetActiveShader(ourShader);
			spriteRenderer->SetLayer(RENDER_LAYER_BACKGROUND);
			tile->GetComponent<Transform*>()->setPosition(leftBounding + x + 0.5, bottomBounding + y + 0.5, -1.0f);
		}
	}

	//chensPlayer1 = new Player(ourShader, texture);
	//Transform* transform = (Transform*)chensPlayer1->GetComponent<Transform*>();
	//transform->setPosition(-7, 2);
	//InputManager* inputManager = InputManager::GetInstance();
	//transform->setScale(3.0f);
//
	//snowBall1 = new Player(ourShader, iceTexture);
	//transform = (Transform*)snowBall1->GetComponent<Transform*>();
	//transform->setPosition(-7, 0);
	//inputManager = InputManager::GetInstance();
	//transform->setScale(1.0f);
//
	//chensPlayer2 = new Player(ourShader, texture2);
	//transform = (Transform*)chensPlayer2->GetComponent<Transform*>();
	//transform->setPosition(10, 2);
	//inputManager = InputManager::GetInstance();
	//transform->setScale(3.0f);
//
	//snowBall2 = new Player(ourShader, iceTexture);
	//transform = (Transform*)snowBall2->GetComponent<Transform*>();
	//transform->setPosition(10, 0);
	//inputManager = InputManager::GetInstance();
	//transform->setScale(1.0f);
}

void PlayerTestScene::OnEnd() {
	delete(chensPlayer1);
	delete(chensPlayer2);
	delete(snowBall1);
	delete(snowBall2);
}

void PlayerTestScene::OnUpdate() {
}