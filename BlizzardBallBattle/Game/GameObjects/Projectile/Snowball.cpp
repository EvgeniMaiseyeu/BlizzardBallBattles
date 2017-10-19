#include "Snowball.h"
#include "Physics.h"
#include "Sprite.h"
#include "SpriteRenderer.h"

Snowball::Snowball(GameObject* player, float playerPower, float radians, Shader* shader, GLuint textureBufferID) : GameObject(false),_player(player) {
	Physics* physics = new Physics(this);
	AddComponent<Physics*>(physics);
	GetComponent<Transform*>()->setX(_player->GetComponent<Transform*>()->getX());
	GetComponent<Transform*>()->setY(_player->GetComponent<Transform*>()->getY());

	AddComponent<Collider*>(new Collider(this, 50.0f));
	//AddComponent<Collider*>(new Collider(this, GetComponent<Transform*>()->getScale()/2));
	myCollider = GetComponent<Collider*>();

	_speed = playerPower;
	Vector2* velocity = new Vector2(1, 0);

	velocity = *velocity * _speed;
	velocity->rotateVector(radians);
	physics->setVelocity(velocity);

	AddComponent<SpriteRenderer*>(new SpriteRenderer(this));

	SpriteRenderer* renderer = (SpriteRenderer*)GetComponent<SpriteRenderer*>();
	renderer->SetActiveShader(shader);
	renderer->SetActiveSprite(new Sprite(textureBufferID));
}

void Snowball::OnUpdate(int timeDelta)
{
	if (myCollider->collisionDetected())
	{
		Battler *hitBattler = dynamic_cast<Battler*>(myCollider->getColliderObj());
		if (hitBattler)
		{

		}
	}
}


	

