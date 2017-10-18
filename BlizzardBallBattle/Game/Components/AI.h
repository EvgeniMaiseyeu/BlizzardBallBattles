#pragma once

#include "Component.h"
#include "GameObject.h"
#include "Battler.h"
#include "Transform.h"

class AI :
	public Component
{
private:
	Battler *myBattler;
	Transform *myTransform;
	GameObject *target;
	void EngageTarget(float deltaTIme);
	void AI::WalkToTarget(float deltaTime);
	void AI::Shoot();
	GameObject* GetTarget();
	bool AI::CanMakeDecision(float deltaTIme);

	float decisionFrequency;
	float timeSinceLastDecision;
	float intelligence;
	bool lastActionWasShooting;

public:
	AI(GameObject* gameObject);
	~AI();
	void Init();
	GameObject* GetTarget();
	void OnStart(){};
	void OnUpdate(int ticks){};
	void OnEnd(){};
};

#endif