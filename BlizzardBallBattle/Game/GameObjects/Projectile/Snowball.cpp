#include "Snowball.h"
#include "Physics.h"
#include "SharedConstants.h"
#include "SpriteRendererManager.h"
#include "PhysicsManager.h"
#include "Collision/Collider.h"

Snowball::Snowball(GameObject* player, float playerPower, float radians, std::string textureFileName) : SimpleSprite(textureFileName, 0.0f, 0.0f),_player(player) {
	Physics* physics = new Physics(this);
	AddComponent<Physics*>(physics);
	GetComponent<Transform*>()->setX(_player->GetComponent<Transform*>()->getX());
	GetComponent<Transform*>()->setY(_player->GetComponent<Transform*>()->getY());
	GetComponent<Transform*>()->setScale(0.5f);

	//AddComponent<Collider*>(new Collider(this, 50.0f));
	AddComponent<Collider*>(new Collider(this, GetComponent<Transform*>()->getScale()/4));
	myCollider = GetComponent<Collider*>();

	_speed = playerPower;
	Vector2* velocity = new Vector2(1, 0);

	velocity = *velocity * _speed;
	velocity->rotateVector(radians);
	physics->setVelocity(velocity);
	active = true;
}

void Snowball::OnUpdate(int timeDelta)
{
	if (active) {
		if (myCollider->collisionDetected())
		{
			Battler *hitBattler = dynamic_cast<Battler*>(myCollider->getColliderObj());
			if (hitBattler)
			{

			}
		}
		float x = GetComponent<Transform*>()->getX();
		if (x < -GAME_WIDTH / 2 || x > GAME_WIDTH / 2) {
			SpriteRendererManager::GetInstance()->RemoveSpriteFromRendering(GetComponent<SpriteRenderer*>());
			PhysicsManager::GetInstance()->removeCollider(GetComponent<Collider*>());
			//remove self from rendering, physics, and stop checking for collision detection
			active = false;
		}
	}
}


	

