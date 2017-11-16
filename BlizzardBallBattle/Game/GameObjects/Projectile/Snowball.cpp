#include "Snowball.h"
#include "Physics.h"
#include "SharedConstants.h"
#include "SpriteRendererManager.h"
#include "PhysicsManager.h"
#include "Collision/Collider.h"

Snowball::Snowball(GameObject* player, float playerPower, float radians, std::string textureFileName) : SimpleSprite(textureFileName, 0.0f, 0.0f),_player(player) {
	Physics* physics = new Physics(this);
	AddComponent<Physics*>(physics);
	GetTransform()->setX(_player->GetTransform()->getX());
	GetTransform()->setY(_player->GetTransform()->getY());
	GetTransform()->setScale(0.5f);

	//AddComponent<Collider*>(new Collider(this, 50.0f));
	AddComponent<Collider*>(new Collider(this, GetTransform()->getScale()/2));
	myCollider = GetComponent<Collider*>();

	_speed = playerPower;
	Vector2* velocity = new Vector2(1, 0);

	velocity = *velocity * _speed;
	velocity->rotateVector(radians);
	physics->setVelocity(velocity);
	active = true;
	heldByPlayer = false;
}

void Snowball::OnUpdate(int timeDelta)
{
	if (heldByPlayer) {
		if (dynamic_cast<Battler*>(_player)->stats.teamID == 1) {
			GetTransform()->setX(_player->GetTransform()->getX() + 0.7f);
			GetTransform()->setY(_player->GetTransform()->getY());
		}
		else {
			GetTransform()->setX(_player->GetTransform()->getX() - 0.7f);
			GetTransform()->setY(_player->GetTransform()->getY());
		}
	}
	if (active) {
		if(!heldByPlayer)
			GetTransform()->addRotation(15);

		if (myCollider->collisionDetected())
		{
			std::vector<GameObject*> v = myCollider->getColliders();
			for (int i = 0; i < v.size(); i++) {
				Battler *hitBattler = dynamic_cast<Battler*>(v[i]);
				if (hitBattler && (v[i]->getId() != _player->getId())) {
					//yes we hit do stuff
					if (hitBattler->stats.teamID != dynamic_cast<Battler*>(_player)->stats.teamID) {
						hitBattler->DealtDamage(1);
						SpriteRendererManager::GetInstance()->RemoveSpriteFromRendering(GetComponent<SpriteRenderer*>());
						PhysicsManager::GetInstance()->removeCollider(GetComponent<Collider*>());

						//remove self from rendering, physics, and stop checking for collision detection
						active = false;
					}
				}
			}
		}

		float x = GetTransform()->getX();
		if (x < -GAME_WIDTH / 2 || x > GAME_WIDTH / 2) {
			SpriteRendererManager::GetInstance()->RemoveSpriteFromRendering(GetComponent<SpriteRenderer*>());
			PhysicsManager::GetInstance()->removeCollider(GetComponent<Collider*>());
			//remove self from rendering, physics, and stop checking for collision detection
			active = false;
		}
	}
}

void Snowball::setHeld(bool held) {
	heldByPlayer = held;
}
	

