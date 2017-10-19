#pragma once

#include "GameObject.h"
#include "Battler.h"
#include "Collision\Collider.h"
#include "SimpleSprite.h"

class Snowball : public SimpleSprite {
private:
	GameObject* _player;
	float _speed;
	Collider* myCollider;
	
public:
	Snowball(GameObject* player, float playerPower, float radians, std::string textureFileName);
	void OnStart() {};
	void OnUpdate(int ticks);
	void OnEnd() {};
};