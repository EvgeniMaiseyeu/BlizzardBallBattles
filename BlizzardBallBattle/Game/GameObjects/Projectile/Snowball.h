#pragma once

#include "GameObject.h"
#include "Battler.h"
#include "Collision\Collider.h"

class Snowball : public GameObject {
private:
	GameObject* _player;
	float _speed;
	Collider* myCollider;
	
public:
	Snowball(GameObject* player, float playerPower, float radians, Shader* shader, GLuint textureBufferID);
	void OnStart() {};
	void OnUpdate(int ticks);
	void OnEnd() {};
};