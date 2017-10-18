
#include "Snowball.h"
#include "Physics.h"

Snowball::Snowball(GameObject* player, float playerPower, float radians): _player(player) {
	Physics* physics = new Physics(this);
	AddComponent<Physics*>(physics);
	GetComponent<Transform*>()->setX(_player->GetComponent<Transform*>()->getX());
	GetComponent<Transform*>()->setY(_player->GetComponent<Transform*>()->getY());
	_speed = playerPower;
	Vector2* velocity = new Vector2(1, 0);

	velocity = *velocity * _speed;
	velocity->rotateVector(radians);
	physics->setVelocity(velocity);
}

