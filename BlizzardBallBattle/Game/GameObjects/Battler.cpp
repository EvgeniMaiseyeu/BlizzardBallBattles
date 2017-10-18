#include "Battler.h"
#include "Sprite.h"
#include "SpriteRenderer.h"
#include "Transform.h"

Battler::Battler(int team, Shader* shader, GLuint textureBufferID) : GameObject()
{
	AddComponent<SpriteRenderer*>(new SpriteRenderer(this));
	SpriteRenderer* renderer = (SpriteRenderer*)GetComponent<SpriteRenderer*>();
	renderer->SetActiveShader(shader);
	renderer->SetActiveSprite(new Sprite(textureBufferID));

	teamID = team;
	moveSpeed = 1;
}

Battler::~Battler()
{

}

void Battler::MoveTo(GameObject* gameObject)
{
	

}

void Battler::MoveTo(Vector2* position)
{
	//GetComponent<Transform*>()->setPosition(*position->getX, *position->setY);
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


void Battler::ThrowSnowball()
{

//GetComponent <snowball> 

}