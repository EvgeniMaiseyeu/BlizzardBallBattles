#pragma once
#ifndef BATTLER_H
#define BATTLER_H

#include "Component.h"

class Battler :
	public Component
{
public:
	int teamID;
	Battler(GameObject* gameObject, int team);
	~Battler();
	//TODO: Implement vectors
	//void MoveTo(Vector2 position) 
	//void Face(Vector2 position);
	//void TurnTo(Vector2 position);
	void MoveTo(GameObject* gameObject);
	void Face(GameObject* gameObject);
	void TurnTo(GameObject* gameObject);
	void ThrowSnowball();
};

#endif