#pragma once

#include "Component.h"
#include "GameObject.h"
#include "Vector2.h"
#include "ComplexSprite.h"
#include "Physics.h"

class Snowball;

class Battler :
	public ComplexSprite
{
public:
	struct stats {
		int teamID;
		float moveSpeed;
		float fireSpeedInterval;
		int hitpoints;
		bool isPlayer;
		bool isattached;
	};
	stats stats;
	Snowball* _bigSnowball;

	Battler(int team, std::string textureFileName, std::string networkingID, bool isSender);
	Battler(int team, std::string textureFileName);
	//~Battler();

	void MoveTo(Vector2* position);
	void Face(Vector2* position);
	void TurnTo(Vector2* position);
	bool Move(Vector2* v);
	void MoveTo(GameObject* gameObject);
	void Face(GameObject* gameObject);
	void TurnTo(GameObject* gameObject);
	void OnStart() {};
	void OnUpdate(int ticks);
	void OnEnd() {};
	bool ThrowSnowball();
	bool IsAttached();

	//Big snowball methods//
	void handleBigThrow(float deltaTime);
	bool makeBigSnowball(float deltaTime);
	void animateCreation();
	void handleCancels();
	bool fireBigSnowball();
	bool getBigSnowball();
	void lockToBattler();
	void unlock();
	//--------------------//
	bool DealtDamage(int damage);

private:

	//Big snowball trackers//
	bool _fullLock;
	float _timer;
	bool _haveBigSnowball;
	bool _makingSnowball;
	bool _animate;
	float _throwPower;
	//---------------------//

	Shader* _shader;
	GLuint _textureBufferID;

	Physics* _physics;
	void InitStats(int team);

	void UpdateThrowTimer(float deltaTime);
	void Die();

	bool canFire;
	float timeSinceLastShot;
	bool CheckIfInBounds(Transform *pos, Vector2 *move);

	//Networking
	std::string networkingID;
	bool isSender;

	ComplexSpriteinfo* GenerateSpriteInfo();
};

