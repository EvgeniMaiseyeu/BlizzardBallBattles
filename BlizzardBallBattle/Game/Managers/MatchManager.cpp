#include "MatchManager.h"

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
	if (character->teamID == 1)
	{
		teamOne.push_back(character);
	}
	else if (character->teamID == 2)
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
	// Team 1
	// Player
	GameObject* playerOne = new GameObject();
	Battler* playerOneStats = new Battler(playerOne, 1);
	playerOne->AddComponent<Battler*>(playerOneStats);
	RegisterCharacter(playerOneStats);
	//AI
	for (int i = 0; i < TEAM_SIZE - 1; ++i)
	{
		GameObject* unit = new GameObject();
		Battler* unitStats = new Battler(unit, 1);
		unit->AddComponent<Battler*>(unitStats);
		AI* unitAI = new AI(unit);
		unit->AddComponent<AI*>(unitAI);
		RegisterCharacter(unitStats);
		aiUnits.push_back(unitAI);
	}

	//Team 2
	GameObject* playerTwo = new GameObject();
	Battler* playerTwoStats = new Battler(playerTwo, 2);
	playerTwo->AddComponent<Battler*>(playerTwoStats);
	RegisterCharacter(playerTwoStats);

	for (int i = 0; i < TEAM_SIZE - 1; ++i)
	{
		GameObject* unit = new GameObject();
		Battler* unitStats = new Battler(unit, 2);
		unit->AddComponent<Battler*>(unitStats);
		AI* unitAI = new AI(unit);
		unit->AddComponent<AI*>(unitAI);
		RegisterCharacter(unitStats);
		aiUnits.push_back(unitAI);
	}

	// Initialize our AI
	for (int i = 0; i < aiUnits.size(); ++i)
	{
		aiUnits[i]->Init();
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