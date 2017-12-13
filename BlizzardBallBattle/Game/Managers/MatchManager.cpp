
#include "MatchManager.h"
#include "Sprite.h"
#include "SpriteRenderer.h"
#include "HelperFunctions.h"
#include "UserDefinedRenderLayers.h"
#include "Transform.h"
#include "Player.h"
#include "Sender.h"
#include "Collider.h"
#include <algorithm>
#include "GameManager.h"

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
	TEAM_SIZE = 30;
}

void MatchManager::Stop() {
	while (teamOne.size() > 0) {
		Battler* toDelete = teamOne[0];
		UnRegisterCharacter(toDelete);
		GameManager::GetInstance()->RemoveGameObject(toDelete);
	}
	while (teamTwo.size() > 0) {
		Battler* toDelete = teamTwo[0];
		UnRegisterCharacter(toDelete);
		GameManager::GetInstance()->RemoveGameObject(toDelete);
	}
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

// TODO: Don't call every AI to change targets
bool MatchManager::UnRegisterCharacter(Battler *character)
{
	if (character->stats.teamID == 1)
	{
		teamOne.erase(std::remove(teamOne.begin(), teamOne.end(), character), teamOne.end());
		for (int i = 0; i < teamTwoAIUnits.size(); i++) {
			if (teamTwoAIUnits[i]->currentTarget == teamTwoAIUnits[i]->battler && teamTwoAIUnits[i]->targetBattler == character)
			{
				teamTwoAIUnits[i]->Retarget();
			}
		}
	}
	else if (character->stats.teamID == 2)
	{
		teamTwo.erase(std::remove(teamTwo.begin(), teamTwo.end(), character), teamTwo.end());
		for (int i = 0; i < teamOneAIUnits.size(); i++) {
			if (teamOneAIUnits[i]->currentTarget == teamOneAIUnits[i]->battler && teamOneAIUnits[i]->targetBattler == character)
			{
				teamOneAIUnits[i]->Retarget();
			}
		}
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

void MatchManager::CreateBattlers(Shader *ourShader, GLuint characterTexture, GLuint spriteSheetTexture, int teamOneFormation, int teamTwoFormation)
{
	teamOne.clear();
	teamTwo.clear();
	playerOne = NULL;
	playerTwo = NULL;
	teamOneAIUnits.clear();
	teamTwoAIUnits.clear();

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
	Player* playerOneStats = new Player(playerOne, SDLK_a, SDLK_d, SDLK_w, SDLK_s, SDLK_SPACE, SDLK_x, SDLK_LSHIFT);
	playerOne->AddComponent<Player*>(playerOneStats);
	playerOne->AddComponent<Collider*>(playerOneCollider);
	Transform* playerOneTransform = (Transform*)playerOne->GetTransform();
	playerOneTransform->setPosition(playerPosX, playerPosY);
	playerOne->stats.hitpoints = 5;
	playerOne->stats.isPlayer = true;
	RegisterCharacter(playerOne);

	//AI
	for (int i = 0; i < TEAM_SIZE - 1; ++i)
	{
		bool teamOneLearning = false;
		if (teamOneFormation == 1)
		{
			teamOneLearning = true;
		}

		float posX = randomFloatInRange(-startPosXMin, -startPosXMax);
		float posY = randomFloatInRange(startPosYMin, startPosYMax);

		Battler* unit = new Battler(1, playerSprite);
		AI* unitAI = new AI(unit, teamOneLearning);
		Collider* collider = new Collider(unit, 0.5f);
		unit->AddComponent<AI*>(unitAI);
		unit->AddComponent<Collider*>(collider);
		Transform* aiTransform = (Transform*)unit->GetTransform();
		aiTransform->setPosition(posX, posY);
		RegisterCharacter(unit);
		teamOneAIUnits.push_back(unitAI);
	}


	//Team 2
	playerPosX = randomFloatInRange(startPosXMin, startPosXMax);
	playerPosY = randomFloatInRange(startPosYMin, startPosYMax);
	playerTwo = new Battler(2, playerSprite);
	Collider* playerTwoCollider = new Collider(playerTwo, 0.5f);
	Player* playerTwoStats = new Player(playerTwo, SDLK_LEFT, SDLK_RIGHT, SDLK_UP, SDLK_DOWN, SDLK_RCTRL, SDLK_KP_0, SDLK_RSHIFT);
	playerTwo->AddComponent<Player*>(playerTwoStats);
	playerTwo->AddComponent<Collider*>(playerTwoCollider);
	Transform* playerTwoTransform = (Transform*)playerTwo->GetTransform();
	playerTwoTransform->setPosition(playerPosX, playerPosY);
	playerTwoTransform->addRotation(180.0f);
	playerTwo->stats.hitpoints = 5;
	playerTwo->stats.isPlayer = true;
	RegisterCharacter(playerTwo);

	for (int i = 0; i < TEAM_SIZE - 1; ++i)
	{
		bool teamTwoLearning = false;
		if (teamTwoFormation == 1)
		{
			teamTwoLearning = true;
		}

		float posX = randomFloatInRange(startPosXMin, startPosXMax);
		float posY = randomFloatInRange(startPosYMin, startPosYMax);

		Battler* unit = new Battler(2, playerSprite);
		AI* unitAI = new AI(unit, teamTwoLearning);
		Collider* collider = new Collider(unit, 0.5f);
		unit->AddComponent<AI*>(unitAI);
		unit->AddComponent<Collider*>(collider);
		Transform* aiTransform = (Transform*)unit->GetTransform();
		aiTransform->setPosition(posX, posY);
		aiTransform->addRotation(180.0f);
		RegisterCharacter(unit);
		teamTwoAIUnits.push_back(unitAI);
	}

	// Initialize our AI
	for (int i = 0; i < teamOneAIUnits.size(); ++i)
	{
		float intelligence = randomFloatInRange(0.8f, 1.0f);
		float courage = randomFloatInRange(0.0f, 0.4f);
		float decisionFrequency = randomFloatInRange(0.7f, 2.7f);

		if (teamOneFormation == 3)
		{
			intelligence = randomFloatInRange(0.1f, 0.5f);
			courage = randomFloatInRange(0.8f, 1.0f);
			decisionFrequency = randomFloatInRange(0.5f, 1.5f);
		}

		teamOneAIUnits[i]->Initialize(intelligence, courage, decisionFrequency);
	}
	for (int i = 0; i < teamTwoAIUnits.size(); ++i)
	{
		float intelligence = randomFloatInRange(0.8f, 1.0f);
		float courage = randomFloatInRange(0.0f, 0.4f);
		float decisionFrequency = randomFloatInRange(0.7f, 2.7f);

		if (teamTwoFormation == 3)
		{
			intelligence = randomFloatInRange(0.1f, 0.5f);
			courage = randomFloatInRange(0.8f, 1.0f);
			decisionFrequency = randomFloatInRange(0.5f, 1.5f);
		}

		teamTwoAIUnits[i]->Initialize(intelligence, courage, decisionFrequency);
	}

	teamOneNet = AILearning();
	teamTwoNet = AILearning();
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