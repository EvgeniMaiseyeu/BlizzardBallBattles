#pragma once
#ifndef BATTLER_H
#define BATTLER_H

#include "Component.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Vector2.h"

class Battler :
	public GameObject
{
public:
	int teamID;
	float moveSpeed;
	Battler(int team, Shader* shader, GLuint textureBufferID);
	~Battler();

	void MoveTo(Vector2* position);
	void Face(Vector2* position);
	void TurnTo(Vector2* position);
	void Move(float x, float y);
	void MoveTo(GameObject* gameObject);
	void Face(GameObject* gameObject);
	void TurnTo(GameObject* gameObject);
	void ThrowSnowball();
};

#endif