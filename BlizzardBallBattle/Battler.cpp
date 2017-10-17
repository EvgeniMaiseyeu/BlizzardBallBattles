#include "Battler.h"


Battler::Battler(int team, Shader* shader, GLuint textureBufferID) : GameObject()
{
	teamID = team;
	AddComponent<SpriteRenderer*>(new SpriteRenderer(this));
	SpriteRenderer* renderer = (SpriteRenderer*)GetComponent<SpriteRenderer*>();
	renderer->SetActiveShader(shader);
	renderer->SetActiveTexture(textureBufferID);
	moveSpeed = 1;
}

Battler::~Battler()
{

}

void Battler::MoveTo(GameObject* gameObject)
{

}

void Battler::Move(Vector2 position)
{
	GetComponent<Transform*>()->setPosition(position.getX(), position.getY());
}

void Battler::Face(GameObject* gameObject)
{

}

void Battler::TurnTo(GameObject* gameObject)
{

}

void Battler::ThrowSnowball()
{

}