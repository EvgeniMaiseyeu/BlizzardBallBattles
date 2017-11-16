#include "Snowball.h"
#include "Physics.h"
#include "SharedConstants.h"
#include "SpriteRendererManager.h"
#include "PhysicsManager.h"
#include "Collision/Collider.h"
#include "UserDefinedRenderLayers.h"


Snowball::Snowball(GameObject* player, float playerPower, float radians, std::string textureFileName) : SimpleSprite(textureFileName, 0.0f, 0.0f),_player(player) {
	_physics = new Physics(this);
	AddComponent<Physics*>(_physics);
	GetTransform()->setX(_player->GetTransform()->getX());
	GetTransform()->setY(_player->GetTransform()->getY());
	GetTransform()->setScale(0.5f);

	//AddComponent<Collider*>(new Collider(this, 50.0f));
	AddComponent<Collider*>(new Collider(this, GetTransform()->getScale() / 2));
	myCollider = GetComponent<Collider*>();

	_speed = playerPower;
	Vector2* velocity = new Vector2(1, 0);

	velocity = *velocity * _speed;
	velocity->rotateVector(radians);
	_physics->setVelocity(velocity);
	active = true;
	GetComponent<SpriteRenderer*>()->SetLayer(RENDER_LAYER_SHADOWABLE);
	heldByPlayer = false;
}

void Snowball::OnUpdate(int timeDelta)
{
	if (_distanceGoal != 0 && _distanceTraveled >= _distanceGoal) {
		//DESTROOOOOOOOOY
	}
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
	else {
		_distanceTraveled += _physics->getVelocity()->getX() * timeDelta;
	}
	if (active) {
		if(!heldByPlayer)
			GetTransform()->addRotation(15);

		if (myCollider->collisionDetected())
		{
			std::vector<GameObject*> v = myCollider->getColliders();
			for (int i = 0; i < v.size(); i++) {
				if (v[i] == NULL || v[i] == nullptr || v[i]->GetTransform() == NULL || v[i]->GetTransform() == nullptr) {
					continue;
				}
				Battler *hitBattler = dynamic_cast<Battler*>(v[i]);
				if (hitBattler && (v[i]->getId() != _player->getId())) {
					//yes we hit do stuff
					if (hitBattler->stats.teamID != dynamic_cast<Battler*>(_player)->stats.teamID) {
						if (hitBattler->DealtDamage(1)) {
							Destroy(v[i]);
						}
						DestructSnowball();
						return;
					}
				}
			}
		}

		float x = GetTransform()->getX();
		if (x < -GAME_WIDTH / 2 || x > GAME_WIDTH / 2) {
			Destroy(this);
		}
	}
}

void Snowball::DestructSnowball() {
	Destroy(this); //TODO: Fix with Snowball Destruction
}

void Snowball::setHeld(bool held) {
	heldByPlayer = held;
}
	
void Snowball::setDistanceGoal(float dist) {
	_distanceGoal = dist;
}
