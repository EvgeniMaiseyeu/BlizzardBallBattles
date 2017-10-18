#include "Battler.h"
#include "Sprite.h"
#include "SpriteRenderer.h"
#include "Transform.h"
#include "Snowball.h"

Battler::Battler(int team, Shader* shader, GLuint textureBufferID) : GameObject(false), _shader(shader), _textureBufferID(textureBufferID)
{
	AddComponent<SpriteRenderer*>(new SpriteRenderer(this));
	SpriteRenderer* renderer = (SpriteRenderer*)GetComponent<SpriteRenderer*>();
	renderer->SetActiveShader(shader);
	renderer->SetActiveSprite(new Sprite(textureBufferID));
	
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
}

void Battler::MoveTo(GameObject* gameObject)
{
	

}

void Battler::MoveTo(Vector2* position)
{
	GetComponent<Transform*>()->setPosition(position->getX(), position->getY());
}

void Battler::Move(float x, float y)
{
	//GetComponent<Transform*>()->addTranslation(position->getX(), position->getY());
	GetComponent<Transform*>()->addTranslation(x, y);
	
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
	float radians = GetComponent<Transform*>()->getRotation() * M_PI / 180;
	Snowball* snowball = new Snowball(this, 10, radians, _shader, _textureBufferID);



	return true;
}