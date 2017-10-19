#pragma once

#include "GameObject.h"
#include "Battler.h"

class Snowball : public GameObject {
private:
	GameObject* _player;
	float _speed;
	
public:
	Snowball(GameObject* player, float playerPower, float radians, Shader* shader, GLuint textureBufferID);
	void PressedShoot();
	~Snowball();
};