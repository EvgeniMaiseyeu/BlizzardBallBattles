#pragma once

#include "Component.h"
#include "GameObject.h"
#include "Vector2.h"
#include "SimpleSprite.h"

class Battler :
	public SimpleSprite
{
public:
	struct stats {
		int teamID;
		float moveSpeed;
		float fireSpeedInterval;
		int hitpoints;
		bool isPlayer;
	};
	stats stats;

	Battler(int team, std::string textureFileName, std::string networkingID, bool isSender);
	Battler(int team, std::string textureFileName);
	~Battler();

	void MoveTo(Vector2* position);
	void Face(Vector2* position);
	void TurnTo(Vector2* position);
	void Move(float x, float y);
	void MoveTo(GameObject* gameObject);
	void Face(GameObject* gameObject);
	void TurnTo(GameObject* gameObject);
	void OnStart(){};
	void OnUpdate(int ticks);
	void OnEnd(){};
	bool ThrowSnowball();
	void DealtDamage(int damage);

private:
	Shader* _shader;
	GLuint _textureBufferID;
	void InitStats(int team);

	void UpdateThrowTimer(float deltaTime);
	void Die();

	bool canFire;
	float timeSinceLastShot;

	//Networking
	std::string networkingID;
	bool isSender;
};

