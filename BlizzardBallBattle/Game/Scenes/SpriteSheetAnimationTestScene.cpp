#include "SpriteSheetAnimationTestScene.h"
#include "SpriteRendererManager.h"
#include "Shader.h"
#include "HelperFunctions.h"
#include "SharedConstants.h"
#include "SpriteRenderer.h"
#include "UserDefinedRenderLayers.h"
#include "SpriteSheet.h"
#include <iostream>

int animationCounter = 0;

void SpriteSheetAnimationTestScene::OnStart() {
	ourShader = new Shader(BuildPath("Game/Assets/Shaders/vertex_shader.vs").c_str(), BuildPath("Game/Assets/Shaders/fragment_shader.fs").c_str());
	GLuint texture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/Character.png"));

	float width = getGameWidth();
	float height = getGameHeight();
	float leftBounding = getGameLeftX();
	float bottomBounding = getGameBottomY();

	GLuint spriteSheetTexture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/WalkingSpriteSheet.png"));
	player1 = new GameObject();
	player1->AddComponent<SpriteRenderer*>(new SpriteRenderer(player1));
	SpriteRenderer* spriteRenderer = player1->GetComponent<SpriteRenderer*>();
	spriteRenderer->SetActiveSprite((ISprite*)new SpriteSheet(spriteSheetTexture, 5, 3, 1));
	spriteRenderer->SetActiveShader(ourShader);
}

void SpriteSheetAnimationTestScene::OnEnd() {
	delete(player1);
	delete(player2);
}

void SpriteSheetAnimationTestScene::OnUpdate() {
	animationCounter++;
	if (animationCounter % 10 == 2) {
		SpriteSheet* sprite = (SpriteSheet*)player1->GetComponent<SpriteRenderer*>()->GetSprite();
		sprite->NextIndex();
	}
}