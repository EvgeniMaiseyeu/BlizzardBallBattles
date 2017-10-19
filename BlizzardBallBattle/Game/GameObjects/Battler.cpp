#include "Battler.h"
#include "Transform.h"
#include "HelperFunctions.h"
#include "Snowball.h"
#include "MessageManager.h"
#include "AI.h"

Battler::Battler(int team, std::string textureFileName) : SimpleSprite(textureFileName, 0.0f, 0.0f)
{
	InitStats(team);
}

Battler::~Battler()
{

}

void Battler::InitStats(int team)
{
	stats.teamID = team;
	stats.moveSpeed = 1;
	stats.fireSpeedInterval = 1;
	stats.isPlayer = false;
	stats.hitpoints = 1;
}

void Battler::OnUpdate(int ticks)
{
	float deltaTime = (float)ticks / 1000.0f;

  	UpdateThrowTimer(deltaTime);
}

void Battler::MoveTo(GameObject* gameObject)
{
	

}

void Battler::MoveTo(Vector2* position)
{
	GetTransform()->setPosition(position->getX(), position->getY());
}

void Battler::Move(float x, float y)
{
	//GetTransform()->addTranslation(position->getX(), position->getY());
	GetTransform()->addTranslation(x, y);
}

void Battler::Face(GameObject* gameObject)
{

}

void Battler::Face(Vector2* position)
{

}

void Battler::TurnTo(GameObject* gameObject)
{

}

void Battler::TurnTo(Vector2* position)
{

}

bool Battler::ThrowSnowball()
{
	if (!canFire)
 		return false;

	float radians = GetComponent<Transform*>()->getRotation() * M_PI / 180;
	Snowball* snowball = new Snowball(this, 5, radians, "Snowball.png");
	canFire = false;
	return true;
}

void Battler::UpdateThrowTimer(float deltaTime)
{
	timeSinceLastShot += deltaTime;
	if (timeSinceLastShot > stats.fireSpeedInterval)
	{
		canFire = true;
		timeSinceLastShot = 0.0f;
	}
}

void Battler::DealtDamage(int damage)
{
	stats.hitpoints -= damage;
	if (stats.hitpoints <= 0)
	{
		Die();
	}
}

void Battler::Die()
{
	if (stats.isPlayer)
	{
		std::map<std::string, void*> payload;
		payload["teamID"] = new std::string(std::to_string(stats.teamID));
		MessageManager::SendEvent("PlayerWon", payload);
	}
	else
	{
		GetComponent<AI*>()->Died();
		GetTransform()->setScale(0.0f);
		//delete(this);
	}
}
