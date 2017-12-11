#pragma once

#include "Component.h"
#include "GameObject.h"
#include "Vector2.h"
#include "ComplexSprite.h"
#include "Physics.h"

#define SPRITE_IDLE 0
#define SPRITE_WALK 1
#define SPRITE_SIMPLE_THROW 2

class Snowball;

class Battler :
	public ComplexSprite
{
public:
	struct stats {
		int teamID;
		float moveSpeed;
		float runSpeed;
		float fireSpeedInterval;
		int hitpoints;
		bool isPlayer;
		bool isattached;
		bool isRunning;	
	};
	stats stats;
	Snowball* _bigSnowball;
	Snowball* _smallSnowball;


	Battler(int team, std::string textureFileName, std::string networkingID, bool isSender);
	Battler(int team, std::string textureFileName);
	//~Battler();

	void MoveTo(Vector2* position);
	void Face(Vector2* position);
	void TurnTo(Vector2* position);
	bool Move(float x, float y, bool isRunning);
	void MoveTo(GameObject* gameObject);
	void Face(GameObject* gameObject);
	void TurnTo(GameObject* gameObject);
	void OnStart() {};
	void OnUpdate(int ticks);
	void OnEnd() {};
	bool ThrowSnowball();
	bool IsAttached();
	bool CheckAndSetBounds(Transform *pos, Vector2 *move);
	bool ApplyIceSliding(Vector2 *v);
	bool InIceZone(Transform *t);
	Vector2 *GetVelocity();

	//Big snowball methods//
	void HandleBigThrow(float deltaTime);
	bool MakeBigSnowball(float deltaTime);
	void AnimateCreation();
	void HandleCancels();
	bool FireBigSnowball();
	bool GetBigSnowball();
	void LockToBattler(Snowball* sb);
	void Unlock();
	//--------------------//
	// small ball//
	void setCanFire();
	void HandleSmallThrow(float deltaTime);
	bool MakeSmallSnowball();
	bool FireSmallSnowball();
	bool GetSmallSnowball();

	// ----------------//
	bool DealtDamage(int damage);
	Transform* _transform;
	Physics* _physics;

private:

	//small snowball trackers//
	float _maxDestination;
	float _smallThrowPower;
	bool _haveSmallSnowball;
	float _destination;
	bool _canFire;
	//Big snowball trackers//
	bool _fullLock;
	float _timer;
	bool _haveBigSnowball;
	bool _makingSnowball;
	bool _animate;
	float _throwPower;
	float _throwDistance;
	bool attached;
	//---------------------//
	std::vector<Snowball*> attachedSnowballs;
	Shader* _shader;
	GLuint _textureBufferID;

	void InitStats(int team);

	void UpdateThrowTimer(float deltaTime);
	void UpdateAttachedSnowBalls(float deltaTime);
	void Die();

	bool canFire;
	float timeSinceLastShot;

	//Networking
	std::string networkingID;
	bool isSender;

	ComplexSpriteinfo* GenerateSpriteInfo(int team);
};

