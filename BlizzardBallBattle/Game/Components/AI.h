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
	void WalkToTargetBattler(float deltaTime);
	void WalkToTargetPosition(float deltaTime);
	void Shoot();

	bool CanMakeDecision(float deltaTIme);

	float decisionFrequency;
	float timeSinceLastDecision;
	bool lastActionWasShooting;

	float intelligence;
	float courage;

	bool CheckIfInBounds(float x = 0, float y = 0);

public:
	AI(GameObject* gameObject);
	~AI();
	void Init(float _intelligence, float _courage, float _decisionFrequency);
	void OnStart(){};
	void OnUpdate(int ticks);
	void OnEnd(){};
};

