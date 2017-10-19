
#include "Snowball.h"
#include "Physics.h"
#include "Sprite.h"

Snowball::Snowball(GameObject* player, float playerPower, float radians, Shader* shader, GLuint textureBufferID) : GameObject(false),_player(player) {
	Physics* physics = new Physics(this);
	AddComponent<Physics*>(physics);
	GetComponent<Transform*>()->setX(_player->GetComponent<Transform*>()->getX());
	GetComponent<Transform*>()->setY(_player->GetComponent<Transform*>()->getY());

	_collider = new Collider(this, 0.5f);
	AddComponent<Collider*>(_collider);
	//AddComponent<Collider*>(new Collider(this, GetComponent<Transform*>()->getScale()/2));

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
	if (_collider->collisionDetected())
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


	

