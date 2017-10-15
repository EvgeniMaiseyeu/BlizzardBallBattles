#pragma once
#ifndef BATTLER_H
#define BATTLER_H

#include "Component.h"
#include "GameObject.h"
#include "SpriteRenderer.h"

class Battler :
	public GameObject
{
public:
	int teamID;
	float moveSpeed;
	Battler(int team, Shader* shader, GLuint textureBufferID);
	~Battler();
	//TODO: Implement vectors
	//void MoveTo(Vector2 position) 
	//void Face(Vector2 position);
	//void TurnTo(Vector2 position);
	void MoveTo(GameObject* gameObject);
	void Move(Vector2 position);
	void Face(GameObject* gameObject);
	void TurnTo(GameObject* gameObject);
	void ThrowSnowball();
};

#endif