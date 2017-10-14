#include "AI.h"
#include "MatchManager.h"
#include "Vector2.h"

AI::AI() : Component(gameObject)
{
}

AI::~AI()
{
}

void AI::Init()
{
	myBattler = (Battler*)GetGameObject();
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

	return enemyTeam[randomBattler];
}

void AI::EngageTarget()
{
	int targetPosY = target->GetComponent<Transform*>()->getY();
	int myPosY = GetGameObject()->GetComponent<Transform*>()->getY();

	// 2D Engage Target
	//int myPosX = GetGameObject()->GetComponent<Transform>().getX();
	//int targetPosX = target->GetComponent<Transform>().getX();
	//Vector2 posDiff = Vector2((targetPosX - myPosX), (targetPosY - myPosY));
	
	int posDiffY = targetPosY - myPosY;

}

