#include "GameScene.h"
#include "HelperFunctions.h"
#include "SpriteRendererManager.h"
#include "GLHeaders.h"
#include "SpriteRenderer.h"
#include "SpriteSheet.h"
#include "UserDefinedRenderLayers.h"
#include "MessageManager.h"
#include <map>
#include "SceneManager.h"
#include "Scenes.h"
#include "DayNightCamera.h"
#include "GameManager.h"
#include "AudioManager.h"
#include "HelperFunctions.h"
#include "SharedConstants.h"

int playerWonSubscriptionReceipt;

void PlayerWon(std::map<std::string, void*> payload) {
	std::string* teamIDStrptr = (std::string*)payload["teamID"];
	std::string teamIDStr = *teamIDStrptr;
	int teamID = std::stoi(teamIDStr);
	MessageManager::UnSubscribe("PlayerWon", playerWonSubscriptionReceipt);
	SceneManager::GetInstance()->PushScene(new PostGameMenuScene(teamID));
}

GameScene::GameScene(int player1Choice, int player2Choice) {
	MessageManager::Subscribe("PlayerWon", PlayerWon, this);
	Camera::SetActiveCamera(new DayNightCamera());
	AudioManager::GetInstance()->PlayMusic(BuildPath("Game/Assets/Audio/mario_.wav"), 1, 10);
}

void GameScene::BuildBaseScene() {
	GLuint textureTileSet = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/BackgroundTileSet.png"));

	int width = (int)getGameWidth();
	int height = (int)getGameHeight();
	float leftBounding = getGameLeftX();
	float bottomBounding = getGameBottomY() + (getFullBarSize() / GAME_WIDTH) / 2.0f;

	//Game Logic Vars
	int roofWidth = ROOF_WIDTH;
	int iceWidth = ICE_WIDTH; //Even for even screens, odd for odd screens [Odd Untested]
	int altChance = 10;
	int randSeed = SDL_GetTicks(); //Seed it properly
	TileIndex tileIndex;

	//Generate Background
	for (int x = 0; x < width; x++) {
		bool isLeft = x == 0;
		bool isRight = x == width - 1;
		bool isLeftDoorCenter = x == 2;
		bool isRightDoorCenter = x == width - 3;
		bool isSnowy = x < width / 2 - iceWidth / 2 || x > width / 2 + iceWidth / 2;
		bool isDirtSnowBorderLeft = x < width / 2 - iceWidth / 2 - 1;
		bool isDirtSnowBorderRight = x > width / 2 + iceWidth / 2 + 1;

		float farThrough = (float)x / (float)width;

		for (int y = -1; y < height + 1; y++) {
			bool isBottom = y == 0;
			bool isTop = y == ((int)height - 1);

			//Snowy-To-Ice Areas
			if (isSnowy) {
				if (isTop) {
					tileIndex = TileIndex::DirtSnow_Top;
				} else if (isBottom) {
					tileIndex = TileIndex::DirtSnow_Bottom;
				} else {
					tileIndex = TileIndex::Snow_Center;
				}
			} else { 
				if (isDirtSnowBorderLeft) {
					tileIndex = TileIndex::SnowIce_Left;
				} else if (isDirtSnowBorderRight) {
					tileIndex = TileIndex::SnowIce_Right;
				} else if (isTop) {
					tileIndex = TileIndex::DirtSnowIce_Top;
				} else if (isBottom) {
					tileIndex = TileIndex::DirtSnowIce_Bottom;
				} else {
					tileIndex = TileIndex::Ice_Center;
				}
			}

			if (y == -1 || y == height) {
				tileIndex = TileIndex::Dirt_Center;
            }
			 
			GameObject* tile = new GameObject(false);
			tile->AddComponent<SpriteRenderer*>(new SpriteRenderer(tile));
			SpriteRenderer* spriteRenderer = tile->GetComponent<SpriteRenderer*>();
			spriteRenderer->SetActiveSprite((ISprite*)new SpriteSheet(textureTileSet, 8, 4, 0, static_cast<int>(tileIndex)));
			spriteRenderer->SetActiveShader(Shader::GetShader(SHADER_SPRITESHEET));
			spriteRenderer->SetLayer(RENDER_LAYER_BACKGROUND);
			tile->GetTransform()->setPosition(leftBounding + x + 0.5, bottomBounding + y + 0.5, -2.0f);
			thingsToClear.push_back(tile);
		}
	}

	//Generate Tiles. Refactor out
	for (int x = 0; x < width; x++) {
		bool isLeft = x == 0;
		bool isRight = x == width - 1;
		bool isHouse = x < roofWidth - 1 || x >(width - roofWidth);
		bool isLeftDoorCenter = x == 2;
		bool isRightDoorCenter = x == width - 3;

		for (int y = -1; y < height + 1; y++) {
			bool isBottom = y == 0;
			bool isTop = y == ((int)height - 1);
			bool isAlt = (randSeed++ % (altChance * 2 + 1)) == 0;

			tileIndex = TileIndex::Dirt_Center;

			////Left or Right house roofs
			if (isHouse) {
				tileIndex = TileIndex::HouseRight_Right;
			}
			if (isLeftDoorCenter) {
				tileIndex = TileIndex::HouseLeft_Left;
			}
			if (isRightDoorCenter) {
				tileIndex = TileIndex::HouseRight_Center;
			}

			////Corner Cases////
			if (isTop || isBottom) {
				tileIndex = TileIndex::NA;
			}

			if (tileIndex == TileIndex::Dirt_Center || y == -1 || y == height) {
				continue;
			}
			if (tileIndex == TileIndex::NA) {
				continue;
			}

			//TODO: Turn into "TileSprite"
			GameObject* tile = new GameObject(false);
			tile->AddComponent<SpriteRenderer*>(new SpriteRenderer(tile));
			SpriteRenderer* spriteRenderer = tile->GetComponent<SpriteRenderer*>();
			spriteRenderer->SetActiveSprite((ISprite*)new SpriteSheet(textureTileSet, 8, 4, 0, static_cast<int>(tileIndex)));
			spriteRenderer->SetActiveShader(Shader::GetShader(SHADER_SPRITESHEET));
			spriteRenderer->SetLayer(RENDER_LAYER_SHADOWABLE);
			tile->GetTransform()->setPosition(leftBounding + x + 0.5, bottomBounding + y + 0.5, 2.0);
			thingsToClear.push_back(tile);
		}
	}
}

void GameScene::ClearScene() {
	for (int i = 0; i < thingsToClear.size(); i++) {
		GameManager::GetInstance()->RemoveGameObject(thingsToClear[i]);
	}
}

bool GameScene::isInIceZone(float x, float y) {
	float leftBounds = -ICE_WIDTH / 2;
	float rightBounds = ICE_WIDTH / 2;
	return (x >= leftBounds && x <= rightBounds);
}

bool GameScene::isInLeftZone(float x, float y) {
	float leftBounds = -ICE_WIDTH / 2;
	return x < leftBounds;
}

bool GameScene::isInRightZone(float x, float y) {
	float rightBounds = ICE_WIDTH / 2;
	return x > rightBounds;
}

bool GameScene::isInScreenBounds(float x, float y) {
	return isInScreenBounds(x, y);
}

void GameScene::snapToScreenBounds(float *x, float *y) {
	if (*x < getGameLeftX()) {
		*x = getGameLeftX();
	}
	if (*x > getGameRightX()) {
		*x = getGameRightX();
	}
	if (*y > getGameTopY()) {
		*y = getGameTopY();
	}
	if (*y < getGameBottomY()) {
		*y = getGameBottomY();
	}
}

//Returns NULL on failed cast, which if(NULL) is false, and a valid returned type would if(true)
GameScene* GameScene::GetCurrent() {
	return dynamic_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());
}