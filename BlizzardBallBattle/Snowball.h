#pragma once

#include "GameObject.h"

class Snowball : public GameObject {
private:
	GameObject* _player;
	float _speed;
public:
	Snowball(GameObject* player, float playerPower, float radians);

};