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
	
public:
	Snowball(GameObject* player, float playerPower, float radians, std::string textureFileName);
	void OnStart() {};
	void OnUpdate(int ticks);
	void OnEnd() {};
	void DestructSnowball();
	void setHeld(bool held);
};