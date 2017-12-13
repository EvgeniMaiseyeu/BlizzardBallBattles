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
	int teamID;
	int playerID;
	float _distanceTraveled;
	float _distanceGoal;
	float _destination;
	Physics* _physics;
	bool _bigSnowball;
	float _lockOffsetX;
	float _lockOffsetY;
	std::string networkingID;
	bool isSender;

public:
	void Snowball::setBigSnowBall(bool bigSB);
	Snowball(GameObject* player, float playerPower, float radians, std::string textureFileName, float destination, std::string networkID, bool isSender);
	void OnStart() {};
	void OnUpdate(int ticks);
	void OnEnd() {};
	void DestructSnowball();
	void setHeld(bool held);
	void SetDistanceGoal(float dist);
	void SetDestination(float desti);
	void setPower(float value);
	void setLockedOffsetX(float value);
	float getLockedOffsetX();
	void setLockedOffsetY(float value);
	float getLockedOffsetY();

};