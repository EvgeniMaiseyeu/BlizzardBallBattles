#include "MatchManager.h"
#include "Sprite.h"
#include "SpriteRenderer.h"
#include "HelperFunctions.h"
#include "UserDefinedRenderLayers.h"
#include "Transform.h"
#include "Player.h"
#include "Sender.h"
#include "Collider.h"

//Statics must be given definitions
MatchManager* MatchManager::instance;

MatchManager* MatchManager::GetInstance() 
{
	if (instance == NULL)
		instance = new MatchManager();
	return instance;
}

MatchManager::MatchManager()
{

}


MatchManager::~MatchManager()
{

}

bool MatchManager::RegisterCharacter(Battler *character)
{
	if (character->stats.teamID == 1)
	{
		teamOne.push_back(character);
	}
	else if (character->stats.teamID == 2)
	{
		teamTwo.push_back(character);
	}
	else
	{
		return false;
	}

	return true;
}

void MatchManager::StartGame()
{

}

void MatchManager::CreateMap(Shader *ourShader, GLuint snowTexture, GLuint iceTexture)
{
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
}

void MatchManager::CreateBattlers(Shader *ourShader, GLuint characterTexture, GLuint spriteSheetTexture)
{
	float startPosXMax = getGameWidth() / 2;
	float startPosYMax = getGameHeight() / 2;
	float startPosXMin = getGameWidth() / 6;
	float startPosYMin = -startPosYMax;

	float playerPosX = randomFloatInRange(-startPosXMin, -startPosXMax);
	float playerPosY = randomFloatInRange(startPosYMin, startPosYMax);

	// Team 1
	// Player
	Battler* playerOne = new Battler(1, ourShader, characterTexture);
	Collider* collider = new Collider(playerOne, 2);
	Player* playerOneStats = new Player(playerOne, SDLK_a, SDLK_d,SDLK_w,SDLK_s,SDLK_b);
	playerOne->AddComponent<Player*>(playerOneStats);
	playerOne->AddComponent<Collider*>(collider);
	Transform* playerOneTransform = (Transform*)playerOne->GetComponent<Transform*>();
	playerOneTransform->setPosition(playerPosX, playerPosY);
	RegisterCharacter(playerOne);

	//AI
	for (int i = 0; i < TEAM_SIZE - 1; ++i)
	{
		float posX = randomFloatInRange(-startPosXMin, -startPosXMax);
		float posY = randomFloatInRange(startPosYMin, startPosYMax);

		Battler* unit = new Battler(1, ourShader, characterTexture);
		AI* unitAI = new AI(unit);
		Collider* collider = new Collider(unit, 2);
		unit->AddComponent<AI*>(unitAI);
		unit->AddComponent<Collider*>(collider);
		Transform* aiTransform = (Transform*)unit->GetComponent<Transform*>();
		aiTransform->setPosition(posX, posY);
		RegisterCharacter(unit);
		aiUnits.push_back(unitAI);
	}

	//Team 2
	playerPosX = randomFloatInRange(startPosXMin, startPosXMax);
	playerPosY = randomFloatInRange(startPosYMin, startPosYMax);
	Battler* playerTwo = new Battler(2, ourShader, characterTexture);
	collider = new Collider(playerTwo, 2);
	Player* playerTwoStats = new Player(playerTwo, SDLK_4, SDLK_6, SDLK_8, SDLK_5,SDLK_SPACE);
	playerTwo->AddComponent<Player*>(playerTwoStats);
	playerTwo->AddComponent<Collider*>(collider);
	Transform* playerTwoTransform = (Transform*)playerTwo->GetComponent<Transform*>();
	playerTwoTransform->setPosition(playerPosX, playerPosY);
	RegisterCharacter(playerTwo);

	for (int i = 0; i < TEAM_SIZE - 1; ++i)
	{
		float posX = randomFloatInRange(startPosXMin, startPosXMax);
		float posY = randomFloatInRange(startPosYMin, startPosYMax);

		Battler* unit = new Battler(2, ourShader, characterTexture);
		AI* unitAI = new AI(unit);
		Collider* collider = new Collider(unit, 2);
		unit->AddComponent<AI*>(unitAI);
		unit->AddComponent<Collider*>(collider);
		Transform* aiTransform = (Transform*)unit->GetComponent<Transform*>();
		aiTransform->setPosition(posX, posY);
		RegisterCharacter(unit);
		aiUnits.push_back(unitAI);
	}

	// Initialize our AI
	for (int i = 0; i < aiUnits.size(); ++i)
	{
		float intelligence = randomFloatInRange(0.1f, 1.0f);
		float courage = randomFloatInRange(0.0f, 1.0f);
		float decisionFrequency = randomFloatInRange(0.2f, 2.0f);

		aiUnits[i]->Init(intelligence, courage, decisionFrequency);
	}
}

std::vector<Battler*> MatchManager::GetTeam(int teamID)
{
	if (teamID == 1)
	{
		return teamOne;
	}
	else
	{
		return teamTwo;
	}
}