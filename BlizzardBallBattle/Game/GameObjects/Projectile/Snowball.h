#pragma once

#include "GameObject.h"
#include "Battler.h"
#include "Collider.h"
#include "SimpleSprite.h"

class Snowball : public SimpleSprite {
private:
	bool active;
	GameObject* _player;
	float _speed;
	Collider* myCollider;
	bool heldByPlayer;
	float _distanceTraveled;
	float _distanceGoal;
	Physics* _physics;

public:
	Snowball(GameObject* player, float playerPower, float radians, std::string textureFileName);
	void OnStart() {};
	void OnUpdate(int ticks);
	void OnEnd() {};
	void setHeld(bool held);
	void Snowball::setDistanceGoal(float dist);
};