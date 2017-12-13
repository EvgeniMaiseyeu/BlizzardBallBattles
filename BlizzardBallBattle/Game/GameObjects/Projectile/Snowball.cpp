#include "Snowball.h"
#include "Physics.h"
#include "SharedConstants.h"
#include "SpriteRendererManager.h"
#include "PhysicsManager.h"
#include "Collision/Collider.h"
#include "UserDefinedRenderLayers.h"
#include "MessageManager.h"
#include "AudioManager.h"
#include "SceneManager.h"
#include "GameScene.h"
#include <stdlib.h>
#include <stdio.h>
#include "NetworkingManager.h"
#include "Receiver.h"
#include "Sender.h"

#define _CRT_SECURE_NO_WARNINGS


Snowball::Snowball(GameObject* player, float playerPower, float radians, std::string textureFileName, float destination, std::string networkID, bool isSender) : SimpleSprite(textureFileName, 0.0f, 0.0f),_player(player) {

	_physics = new Physics(this);
	AddComponent<Physics*>(_physics);
	GetTransform()->setX(_player->GetTransform()->getX());
	GetTransform()->setY(_player->GetTransform()->getY());
	GetTransform()->setScale(0.5f);
	teamID = dynamic_cast<Battler*>(_player)->stats.teamID;
	playerID = dynamic_cast<Battler*>(_player)->getId();

	//AddComponent<Collider*>(new Collider(this, 50.0f));
	AddComponent<Collider*>(new Collider(this, GetTransform()->getScale() / 2));
	myCollider = GetComponent<Collider*>();

	//add network data
	this->networkingID = networkID;
	this->isSender = isSender;
	if (NetworkingManager::GetInstance ()->IsConnected ()) {
		if (isSender) {
  			AddComponent<Sender*> (new Sender (this, networkID));
		}
		else {
			AddComponent<Receiver*> (new Receiver (this, networkID));
		}
	}

	_speed = playerPower;
	Vector2* velocity = new Vector2(1, 0);

	velocity = *velocity * _speed;
	velocity->rotateVector(radians);
	_physics->setVelocity(velocity);
	active = true;
	GetComponent<SpriteRenderer*>()->SetLayer(RENDER_LAYER_SHADOWABLE);
	heldByPlayer = false;
	_bigSnowball = false;
	_destination = destination;
	//dynamic_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene())->thingsToClear.push_back(this);
}

void Snowball::OnUpdate(int timeDelta)
{
	if (_destination != 0 && _distanceTraveled >= _destination) {
		//GetTransform()->setScale(0.00001f);
		DestructSnowball();
	}
	if (heldByPlayer) {
		myCollider->setDisabled(true);
	}
	else {
		myCollider->setDisabled(false);
	}
	if (_bigSnowball == false)
	{
		if (heldByPlayer) {
			if (dynamic_cast<Battler*>(_player)->stats.teamID == 1) {
				GetTransform()->setX(_player->GetTransform()->getX());
				GetTransform()->setY(_player->GetTransform()->getY() - 0.5f);
			}
			else {
				GetTransform()->setX(_player->GetTransform()->getX());
				GetTransform()->setY(_player->GetTransform()->getY() + 0.5f);
			}
			

		} else {
			if (_distanceTraveled <= _destination - 5 && _distanceTraveled > 5) {
				myCollider->setDisabled(true);
			}
			else {
				myCollider->setDisabled(false);
			}

			_distanceTraveled += abs(_physics->getVelocity()->getX()) * (float)timeDelta / 1000;
			if (_distanceTraveled <= _destination / 2 && _distanceTraveled > 0 && active) {
				GetTransform()->addScale(0.015f );
				//_physics->getVelocity->getX()* - 0.2f;
			} else if (_distanceTraveled >= _destination / 2 && _distanceTraveled <= _destination && _distanceTraveled > 0 && active) {
				GetTransform()->addScale(-0.015f);
				//	_physics->getVelocity->getX()* + 0.2f;
			}
		}

	} else {
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
	}
	
	//If the scene is not a GameScene, destroy self
	if (!dynamic_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene())) {
		Destroy(this);
	}
	//if (heldByPlayer) {
	//	if (dynamic_cast<Battler*>(_player)->stats.teamID == 1) {
	//		GetTransform()->setX(_player->GetTransform()->getX() + 0.7f);
	//		GetTransform()->setY(_player->GetTransform()->getY());
	//	}
	//	else {
	//		GetTransform()->setX(_player->GetTransform()->getX() - 0.7f);
	//		GetTransform()->setY(_player->GetTransform()->getY());
	//_distanceTraveled += _physics->getVelocity()->getX() * timeDelta;
	//	}
	//}

	if (active) {
		if (_distanceGoal != 0 && _distanceTraveled >= _distanceGoal) {
			Destroy(this);
			return;
		}
		if(!heldByPlayer)
			GetTransform()->addRotation(15);

		if (myCollider->collisionDetected())
		{
			std::vector<GameObject*> v = myCollider->getColliders();
			char path[200];

			AudioManager::GetInstance()->PlaySEFhit(BuildPath(path), 1, 10);
			for (int i = 0; i < v.size(); i++) {
				if (v[i] == NULL || v[i] == nullptr || v[i]->GetTransform() == NULL || v[i]->GetTransform() == nullptr) {
					continue;
				}

				Battler *hitBattler = dynamic_cast<Battler*>(v[i]);

				if (hitBattler == nullptr) // || NetworkingManager::GetInstance ()->IsConnected () && !hitBattler->isSender
					continue;

				if (hitBattler && (v[i]->getId() != playerID)) {
					//yes we hit do stuff
					if (hitBattler->stats.teamID != teamID) {
						int damage = 0;
						if (_bigSnowball) {
							damage = 10;
						}
						else {
							damage = 1;
						}
						if (hitBattler->DealtDamage(damage)) {
							//Destroy(v[i]);
							DestructSnowball();
							return;
						}
						else {
							hitBattler->LockToBattler(this);
							_physics->setVelocity(new Vector2(0, 0));
							active = false;
						}

					}
				}
			}
		}

		float x = GetTransform()->getX();
		if (x < -GAME_WIDTH / 2 || x > GAME_WIDTH / 2) {
			DestructSnowball ();
		}
	}
}

void Snowball::DestructSnowball() {
	if (isSender) {
		std::map<std::string, std::string> payload;
		NetworkingManager::GetInstance ()->PrepareMessageForSending (networkingID + "|DESTROYSNOWBALL", payload);
	}
	Destroy(this); //TODO: Fix with Snowball Destruction
}

void Snowball::setHeld(bool held) {
	heldByPlayer = held;
}

void Snowball::setBigSnowBall(bool bigSB) {
	_bigSnowball = bigSB;
	/*if (bigSB) {
		Battler* player = dynamic_cast<Battler*>(_player);
		if (player) {
			std::string snowball;
			if (player->stats.teamID == 1) {
				snowball = "Snowball2big.png";
			}
			else {
				snowball = "Snowball3big.png";
			}
			GLuint titleTexture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath((char*)snowball.c_str()));
			Sprite* sprite = new Sprite(titleTexture);
			this->GetComponent<SpriteRenderer*>()->SetActiveSprite(sprite);
		}
	}*/
	
}
	
void Snowball::SetDistanceGoal(float dist) {
	_distanceGoal = dist;
}


void Snowball::SetDestination(float desti) {
	_destination = desti;
}

void Snowball::setPower(float value)
{
	_speed = value;
}

void Snowball::setLockedOffsetX(float value)
{
	_lockOffsetX = value;
}

float Snowball::getLockedOffsetX()
{
	return _lockOffsetX;
}

void Snowball::setLockedOffsetY(float value)
{
	_lockOffsetY = value;
}

float Snowball::getLockedOffsetY()
{
	return _lockOffsetY;

}
