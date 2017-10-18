#include "AI.h"
#include "MatchManager.h"
#include "Vector2.h"
#include "Transform.h"
#include <vector>
#include <iostream>
#include <cstdlib>

AI::AI(GameObject* gameObject) : Component(gameObject)
{
	myBattler = (Battler*)GetGameObject();
	myTransform = myBattler->GetComponent<Transform*>();

	intelligence = 0.5f;
	decisionFrequency = 1.0f;
	timeSinceLastDecision = 0.0f;
	lastActionWasShooting = true;
}

AI::~AI()
{

}

void AI::Init()
{
	target = GetTarget();
}

void AI::Update(int timeDelta) 
{
	float deltaTime = (float)timeDelta / 1000.0f;

	EngageTarget(deltaTime);
}

GameObject* AI::GetTarget()
{
	int enemyTeamNumber = 1;
	if (myBattler->stats.teamID == 1)
	{
		enemyTeamNumber = 2;
	}
	std::vector<Battler*> enemyTeam = MatchManager::GetInstance()->GetTeam(enemyTeamNumber);
	int randomBattler = std::rand() % enemyTeam.size();

	return enemyTeam[randomBattler];
}

void AI::EngageTarget(float deltaTime)
{
	if (lastActionWasShooting && !CanMakeDecision(deltaTime))
		return;

	float targetPosY = target->GetComponent<Transform*>()->getY();
	float myPosY = myTransform->getY();

	float posDiffY = targetPosY - myPosY;

	if (posDiffY >= -1 && posDiffY <= 1)
	{
		Shoot();
	}
	else
	{
		WalkToTarget(deltaTime);
	}
}

void AI::WalkToTarget(float deltaTime)
{
	float targetPosY = target->GetComponent<Transform*>()->getY();
	float myPosY = myTransform->getY();

	float posDiffY = targetPosY - myPosY;

	float moveSpeed = myBattler->stats.moveSpeed * deltaTime;
	int direction = (posDiffY > 0) ? 1 : -1;
	moveSpeed = moveSpeed * direction;
	myBattler->Move(0, moveSpeed);

	lastActionWasShooting = false;
}

void AI::Shoot()
{
	float chanceOfFiring = randomFloatInRange(0.0f, 1.0f);

	if (chanceOfFiring <= intelligence)
	{
		myBattler->ThrowSnowball();
		lastActionWasShooting = true;
		target = GetTarget();
	}
}

bool AI::CanMakeDecision(float deltaTIme)
{
	timeSinceLastDecision += deltaTIme;
	if (timeSinceLastDecision >= decisionFrequency)
	{
		timeSinceLastDecision = 0.0f;
		return true;
	}

	return false;
}