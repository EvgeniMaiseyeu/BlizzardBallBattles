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

	enum Target {
		battler = 0,
		position = 1,
		t_MAX
	}currentTarget;
	GameObject *targetBattler;
	Vector2 *targetPosition;
	void GetTarget();
	GameObject* GetTargetBattler();
	Vector2* GetTargetPosition();

	enum State {
		idle = 0,
		walk = 1,
		shoot = 2,
		s_MAX
	}currentState;
	void AI::WalkToTargetBattler(float deltaTime);
	void AI::WalkToTargetPosition(float deltaTime);
	void AI::Shoot();

	bool AI::CanMakeDecision(float deltaTIme);
	void EngageTarget(float deltaTIme);

	float decisionFrequency;
	float timeSinceLastDecision;
	bool lastActionWasShooting;

	float intelligence;
	float courage;

public:
	AI(GameObject* gameObject);
	~AI();
	void Init();
	void OnStart(){};
	void OnUpdate(int ticks);
	void OnEnd(){};
};

