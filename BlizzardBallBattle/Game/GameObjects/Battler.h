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
	struct stats {
		int teamID;
		float moveSpeed;
		float fireSpeedInterval;
		int hitpoints;
	};
	stats stats;

	Battler(int team, Shader* shader, GLuint textureBufferID);
	~Battler();


	void MoveTo(Vector2* position);
	void Face(Vector2* position);
	void TurnTo(Vector2* position);
	void Move(float x, float y);
	void MoveTo(GameObject* gameObject);
	void Face(GameObject* gameObject);
	void TurnTo(GameObject* gameObject);
	void OnStart(){};
	void OnUpdate(int ticks){};
	void OnEnd(){};
	bool ThrowSnowball();

private:
	Shader* _shader;
	GLuint _textureBufferID;
	void InitStats(int team);

	bool canFire;
	bool timeSinceLastShot;
};

#endif