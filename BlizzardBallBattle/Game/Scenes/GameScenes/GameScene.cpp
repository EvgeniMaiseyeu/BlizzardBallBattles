#include "GameScene.h"
#include "HelperFunctions.h"
#include "SpriteRendererManager.h"
#include "GLHeaders.h"
#include "SpriteRenderer.h"
#include "SpriteSheet.h"
#include "UserDefinedRenderLayers.h"

void GameScene::BuildBaseScene() {
    ourShader = new Shader(BuildPath("Game/Assets/Shaders/tile.vs").c_str(), BuildPath("Game/Assets/Shaders/fragment_shader.fs").c_str());
	GLuint textureTileSet = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/BackgroundTileSet.png"));

	int width = (int)getGameWidth();
	int height = (int)getGameHeight();
	float leftBounding = getGameLeftX();
	float bottomBounding = getGameBottomY() + (getFullBarSize() / GAME_WIDTH) / 2.0f;

	//Game Logic Vars
	int roofWidth = 3;
	int iceWidth = 8; //Even for even screens, odd for odd screens [Odd Untested]
	int altChance = 10;
	int randSeed = SDL_GetTicks(); //Seed it properly
	TileIndex tileIndex;

	//Generate Tiles. Refactor out
	for (int x = 0; x < width; x++) {
		bool isLeft = x == 0;
		bool isRight = x == width - 1;
		bool isHouse = x < roofWidth - 1 || x >(width - roofWidth);
		bool isLeftDoorCenter = x == 2;
		bool isRightDoorCenter = x == width - 3;
		bool isSnowy = x < width / 2 - iceWidth / 2 || x > width / 2 + iceWidth / 2;
		bool isDirtSnowBorderLeft = x < width / 2 - iceWidth / 2 - 1;
		bool isDirtSnowBorderRight = x > width / 2 + iceWidth / 2 + 1;

		for (int y = -1; y < height + 1; y++) {
			bool isBottom = y == 0;
			bool isTop = y == ((int)height - 1);
			bool isAlt = (randSeed++ % (altChance * 2 + 1)) == 0;

			std::cout << y << " == " << (height - 1) << " = " << isTop << std::endl;
			//TODO: Change to assignting TileIndex and doing one single cast at the end
			//Snowy-To-Ice Areas
			if (isSnowy) {
				randSeed++;
				if (isTop) {
					tileIndex = TileIndex::DirtSnow_Top;
				}
				else if (isBottom) {
					tileIndex = TileIndex::DirtSnow_Bottom;
				}
				else {
					randSeed++;
					if (isAlt) {
						if (x % 3 == 2) {
							tileIndex = TileIndex::Snow_Center_Alt1_Shrub;
						}
						else if (y % 3 == 2 || x % 4 == 2) {
							tileIndex = TileIndex::Snow_Center_Alt2_Shrub;
						}
						else if (x % 2 == 0) {
							tileIndex = TileIndex::Snow_Center_Alt3_Shrub;
						}
						else if (y % 2 == 0 && x % 3 == 0) {
							tileIndex = TileIndex::Snow_Center_Alt4_Snowman;
						}
						else {
							tileIndex = TileIndex::Snow_Center;
						}
					}
					else {
						tileIndex = TileIndex::Snow_Center;
						randSeed++;
					}
				}
			}
			else {
				if (isDirtSnowBorderLeft) {
					randSeed++;
					tileIndex = TileIndex::SnowIce_Left;
				}
				else if (isDirtSnowBorderRight) {
					tileIndex = TileIndex::SnowIce_Right;
				}
				else if (isTop) {
					tileIndex = TileIndex::DirtSnowIce_Top;
				}
				else if (isBottom) {
					tileIndex = TileIndex::DirtSnowIce_Bottom;
				}
				else {
					tileIndex = TileIndex::Ice_Center;
				}
			}

			////Left or Right house roofs
			if (isHouse) {
				randSeed++;
				std::cout << x << std::endl;
				tileIndex = TileIndex::HouseLeft_Left;
			}
			if (isLeftDoorCenter) {
				randSeed++;
				std::cout << "LeftHouse";
				if (isAlt) {
					tileIndex = TileIndex::HouseLeft_Center_Alt;
				}
				else {
					tileIndex = TileIndex::HouseLeft_Center;
				}
			}
			if (isRightDoorCenter) {
				std::cout << "RightHouse";
				if (isAlt) {
					randSeed++;
					tileIndex = TileIndex::HouseRight_Center_Alt;
				}
				else {
					randSeed++;
					tileIndex = TileIndex::HouseRight_Center;
				}
			}

			////Corner Cases////
			if (isTop) {
				if (isLeft) {
					std::cout << "TOPLEFT";
					tileIndex = TileIndex::DirtHouseLeft_TopLeft;
				}
				else if (isRight) {
					std::cout << "TOPRIGHT";
					tileIndex = TileIndex::DirtHouseRight_TopRight;
				}
				else if (isHouse) {
					std::cout << "isLeftDoorHouse : isRightDoorHouse";
					tileIndex = TileIndex::DirtHouseLeft_TopLeft;
				}
				else if (isLeftDoorCenter) {
					std::cout << "isLeftDoorCenter";
					tileIndex = TileIndex::DirtHouseLeft_Top;
				}
				else if (isRightDoorCenter) {
					std::cout << "isRightDoorCenter";
					tileIndex = TileIndex::DirtHouseRight_Top;
				}
			}
			else if (isBottom) {
				if (isLeft) {
					std::cout << "BOTTOMLEFT";
					tileIndex = TileIndex::DirtHouseLeft_BottomLeft;
				}
				else if (isRight) {
					std::cout << "BOTTOMRIGHT";
					tileIndex = TileIndex::DirtHouseRight_BottomRight;
				}
				else if (isHouse) {
					std::cout << "isLeftDoorHouse : isRightDoorHouse";
					tileIndex = TileIndex::DirtHouseLeft_BottomLeft;
				}
				else if (isLeftDoorCenter) {
					std::cout << "isLeftDoorCenter";
					tileIndex = TileIndex::DirtHouseLeft_Bottom;
				}
				else if (isRightDoorCenter) {
					std::cout << "isRightDoorCenter";
					tileIndex = TileIndex::DirtHouseRight_Bottom;
				}
			}

			if (y == -1 || y == height) {
				tileIndex = TileIndex::Dirt_Center;
            }

            //TODO: Turn into "TileSprite"
			GameObject* tile = new GameObject(false);
			tile->AddComponent<SpriteRenderer*>(new SpriteRenderer(tile));
			SpriteRenderer* spriteRenderer = tile->GetComponent<SpriteRenderer*>();
			spriteRenderer->SetActiveSprite((ISprite*)new SpriteSheet(textureTileSet, 8, 4, 0, static_cast<int>(tileIndex)));
			spriteRenderer->SetActiveShader(ourShader);
			spriteRenderer->SetLayer(RENDER_LAYER_BACKGROUND);
			tile->GetComponent<Transform*>()->setPosition(leftBounding + x + 0.5, bottomBounding + y + 0.5, -1.0f);
		}
	}
}