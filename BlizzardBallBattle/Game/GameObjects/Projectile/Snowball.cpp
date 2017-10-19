#include "Snowball.h"
#include "Physics.h"

Snowball::Snowball(GameObject* player, float playerPower, float radians, std::string textureFileName) : SimpleSprite(textureFileName, 0.0f, 0.0f),_player(player) {
	Physics* physics = new Physics(this);
	AddComponent<Physics*>(physics);
	GetComponent<Transform*>()->setX(_player->GetComponent<Transform*>()->getX());
	GetComponent<Transform*>()->setY(_player->GetComponent<Transform*>()->getY());

	_collider = new Collider(this, GetComponent<Transform*>()->getScale() / 2);
	AddComponent<Collider*>(_collider);

	_speed = playerPower;
	Vector2* velocity = new Vector2(1, 0);

	velocity = *velocity * _speed;
	velocity->rotateVector(radians);
	physics->setVelocity(velocity);
}

void Snowball::OnUpdate(int timeDelta)
{
	GetComponent <Transform*>()->addRotation(15);

	if (myCollider->collisionDetected())
	{
		std::vector<GameObject*> v = _collider->getColliders();
		for (int i = 0; i < v.size(); i++) {
			Battler *hitBattler = dynamic_cast<Battler*>(v[i]);
			if (hitBattler && (v[i]->getId() != _player->getId()))
			{
				//yes we hit do stuff
			}
		}
 		//Battler *hitBattler = dynamic_cast<Battler*>(myCollider->getColliderObj());
 		
	}
}


	

