#include "AI.h"
#include "MatchManager.h"

AI::AI(GameObject* gameObject) : Component(gameObject)
{
	try {
		// Ensure that the gameobject this AI component is on has a Battler component
		Battler* battler = (Battler*)gameObject->GetComponent("Battler");
		myBattler = battler;
	}
	catch (...) {
		throw;
	}
}

AI::~AI()
{

}

void AI::Init()
{
	target = GetTarget();
}

GameObject* AI::GetTarget()
{
	int enemyTeamNumber = 1;
	if (myBattler->teamID == 1)
	{
		enemyTeamNumber = 2;
	}
	std::vector<Battler*> enemyTeam = MatchManager::GetInstance()->GetTeam(enemyTeamNumber);
	int randomBattler = std::rand() % enemyTeam.size();

	return enemyTeam[randomBattler]->GetGameObject();
}

