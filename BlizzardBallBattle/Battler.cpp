#include "Battler.h"


Battler::Battler(int team, Shader* shader, GLuint textureBufferID) : GameObject()
{
	teamID = team;
	AddComponent<SpriteRenderer*>(new SpriteRenderer(this));
	SpriteRenderer* renderer = (SpriteRenderer*)GetComponent<SpriteRenderer*>();
	renderer->SetActiveShader(shader);
	renderer->SetActiveTexture(textureBufferID);

}

Battler::~Battler()
{

}

void Battler::MoveTo(GameObject* gameObject)
{

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