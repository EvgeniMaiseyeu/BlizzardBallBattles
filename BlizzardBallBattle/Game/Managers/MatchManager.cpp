#include "MatchManager.h"
#include "Sprite.h"
#include "SpriteRenderer.h"
#include "HelperFunctions.h"
#include "UserDefinedRenderLayers.h"
#include "Transform.h"
#include "Player.h"
#include "Sender.h"
#include "Collision\Collider.h"
#include <algorithm>

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
	TEAM_SIZE = 2;
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

bool MatchManager::UnRegisterCharacter(Battler *character)
{
	if (character->stats.teamID == 1)
	{
		teamOne.erase(std::remove(teamOne.begin(), teamOne.end(), character), teamOne.end());
	}
	else if (character->stats.teamID == 2)
	{
		teamTwo.erase(std::remove(teamTwo.begin(), teamTwo.end(), character), teamTwo.end());
	}
	else
	{
		return false;
	}

	if (teamTwo.size() == 1 && teamOne.size() == 1)
	{
		playerOne->stats.fireSpeedInterval = 0;
		playerTwo->stats.fireSpeedInterval = 0;
	}

	return true;
}

void MatchManager::StartGame()
{

}

void MatchManager::CreateBattlers(Shader *ourShader, GLuint characterTexture, GLuint spriteSheetTexture)
{
	float startPosXMax = getGameWidth() / 2;
	float startPosYMax = getGameHeight() / 2;
	float startPosXMin = getGameWidth() / 6;
	float startPosYMin = -startPosYMax;

	float playerPosX = randomFloatInRange(-startPosXMin, -startPosXMax);
	float playerPosY = randomFloatInRange(startPosYMin, startPosYMax);

	std::string playerSprite = "Character.png";

	// Team 1
	// Player
	playerOne = new Battler(1, playerSprite);
	Collider* playerOneCollider = new Collider(playerOne, 0.5f);
	Player* playerOneStats = new Player(playerOne, SDLK_a, SDLK_d, SDLK_w, SDLK_s, SDLK_x);
	playerOne->AddComponent<Player*>(playerOneStats);
	playerOne->AddComponent<Collider*>(playerOneCollider);
	Transform* playerOneTransform = (Transform*)playerOne->GetTransform();
	playerOneTransform->setPosition(playerPosX, playerPosY);
	playerOne->stats.hitpoints = 3;
	playerOne->stats.isPlayer = true;
	RegisterCharacter(playerOne);

	//AI
	for (int i = 0; i < TEAM_SIZE - 1; ++i)
	{
		float posX = randomFloatInRange(-startPosXMin, -startPosXMax);
		float posY = randomFloatInRange(startPosYMin, startPosYMax);

		Battler* unit = new Battler(1, playerSprite);
		AI* unitAI = new AI(unit);
		Collider* collider = new Collider(unit, 0.5f);
		unit->AddComponent<AI*>(unitAI);
		unit->AddComponent<Collider*>(collider);
		Transform* aiTransform = (Transform*)unit->GetTransform();
		aiTransform->setPosition(posX, posY);
		RegisterCharacter(unit);
		aiUnits.push_back(unitAI);
	}

	//Team 2
	playerPosX = randomFloatInRange(startPosXMin, startPosXMax);
	playerPosY = randomFloatInRange(startPosYMin, startPosYMax);
	playerTwo = new Battler(2, playerSprite);
	Collider* playerTwoCollider = new Collider(playerTwo, 0.5f);
	Player* playerTwoStats = new Player(playerTwo, SDLK_l , SDLK_QUOTE, SDLK_p, SDLK_SEMICOLON, SDLK_PERIOD);
	playerTwo->AddComponent<Player*>(playerTwoStats);
	playerTwo->AddComponent<Collider*>(playerTwoCollider);
	Transform* playerTwoTransform = (Transform*)playerTwo->GetTransform();
	playerTwoTransform->setPosition(playerPosX, playerPosY);
	playerTwoTransform->addRotation(180.0f);
	playerTwo->stats.hitpoints = 3;
	playerTwo->stats.isPlayer = true;
	RegisterCharacter(playerTwo);

	for (int i = 0; i < TEAM_SIZE - 1; ++i)
	{
		float posX = randomFloatInRange(startPosXMin, startPosXMax);
		float posY = randomFloatInRange(startPosYMin, startPosYMax);

		Battler* unit = new Battler(2, playerSprite);
		AI* unitAI = new AI(unit);
		Collider* collider = new Collider(unit, 0.5f);
		unit->AddComponent<AI*>(unitAI);
		unit->AddComponent<Collider*>(collider);
		Transform* aiTransform = (Transform*)unit->GetTransform();
		aiTransform->setPosition(posX, posY);
		aiTransform->addRotation(180.0f);
		RegisterCharacter(unit);
		aiUnits.push_back(unitAI);
	}

	// Initialize our AI
	for (int i = 0; i < aiUnits.size(); ++i)
	{
		float intelligence = randomFloatInRange(0.8f, 1.0f);
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