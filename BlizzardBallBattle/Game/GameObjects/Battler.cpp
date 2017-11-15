
#include "Transform.h"
#include "HelperFunctions.h"
#include "MessageManager.h"
#include "AI.h"
#include "NetworkingManager.h"
#include "SpriteRendererManager.h"
#include "PhysicsManager.h"
#include "MatchManager.h"
#include "Physics.h"
#include "Battler.h"

void ReceivedFireSnowball(std::map<std::string, void*> payload) {
	Battler* self = (Battler*)payload["this"];
	self->ThrowSnowball();
}

Battler::Battler(int team, std::string textureFileName, std::string networkingID, bool isSender) : SimpleSprite(textureFileName, 0.0f, 0.0f)
{
	this->networkingID = networkingID;
	this->isSender = isSender;
	if (!isSender) {
		MessageManager::Subscribe(networkingID + "|FIRE", ReceivedFireSnowball, this);
	}

	InitStats(team);
}

Battler::Battler(int team, std::string textureFileName) : SimpleSprite(textureFileName, 0.0f, 0.0f)
{
	InitStats(team);
}

Battler::~Battler()
{

}

void Battler::InitStats(int team)
{
	stats.teamID = team;
	stats.moveSpeed = 2;
	stats.fireSpeedInterval = 1;
	stats.isPlayer = false;
	stats.hitpoints = 1;
}

void Battler::OnUpdate(int ticks)
{
	float deltaTime = (float)ticks / 1000.0f;

  	UpdateThrowTimer(deltaTime);
}

void Battler::MoveTo(GameObject* gameObject)
{
	

}

void Battler::MoveTo(Vector2* position)
{
	GetTransform()->setPosition(position->getX(), position->getY());
}

void Battler::Move(float x, float y)
{
	//GetTransform()->addTranslation(position->getX(), position->getY());
	GetTransform()->addTranslation(x, y);
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

bool Battler::ThrowSnowball()
{
	if (!canFire)
 		return false;

	if (isSender) {
		std::map<std::string, std::string> payload;
		NetworkingManager::GetInstance()->PrepareMessageForSending(networkingID + "|FIRE", payload);
	}

	float radians = GetComponent<Transform*>()->getRotation() * M_PI / 180;

	std::string snowballColour = "Snowball2.png";
	if (stats.teamID == 2)
		snowballColour = "Snowball3.png";

	Snowball* snowball = new Snowball(this, 5, radians, snowballColour);
	canFire = false;
	return true;
}

void Battler::UpdateThrowTimer(float deltaTime)
{
	timeSinceLastShot += deltaTime;
	if (timeSinceLastShot > stats.fireSpeedInterval)
	{
		canFire = true;
		timeSinceLastShot = 0.0f;
	}
}

void Battler::DealtDamage(int damage)
{
	stats.hitpoints -= damage;
	if (stats.hitpoints <= 0)
	{
		Die();
	}
}

void Battler::Die()
{
	if (stats.isPlayer)
	{
		int winningTeam = 1;
		if (stats.teamID == 1)
			winningTeam = 2;

		if (NetworkingManager::GetInstance()->IsConnected() && isSender) {
			std::map<std::string, std::string> payloadNet;
			payloadNet["teamID"] = std::to_string(winningTeam);
			NetworkingManager::GetInstance()->PrepareMessageForSending("PlayerWon", payloadNet);
		}

		std::map<std::string, void*> payload;
		payload["teamID"] = new std::string(std::to_string(winningTeam));
		MessageManager::SendEvent("PlayerWon", payload);
		
	}
	else if (HasComponent<AI*>()) {
		GetComponent<AI*>()->Died();
	}
	else {
		if (networkingID.find("Player") == string::npos) {
			stats.hitpoints = 1;
			return;
		}
		MatchManager::GetInstance()->UnRegisterCharacter(this);
	}

	GetTransform()->setScale(0.0f);
	SpriteRendererManager::GetInstance()->RemoveSpriteFromRendering(GetComponent<SpriteRenderer*>());
	PhysicsManager::GetInstance()->removeCollider(GetComponent<Collider*>());
}

//------------------------------------------------------
//BIG SNOWBALL METHODS
//------------------------------------------------------

//should be called every update for each player/ai on screen
void Battler::handleBigThrow(float deltaTime) {
	if (_fullLock && _timer < 4)
		_timer += deltaTime;
	else if (_fullLock && _timer > 4) {
		//launch snowball
		float radians = GetComponent<Transform*>()->getRotation() * M_PI / 180;
		Vector2* velocity = new Vector2(1, 0);
		velocity = *velocity * _throwPower;
		velocity->rotateVector(radians);
		_bigSnowball->GetComponent<Physics*>()->setVelocity(velocity);
		_haveBigSnowball = false;
		_fullLock = false;
		_throwPower = 0;
	}
}

//keep calling until return true
bool Battler::makeBigSnowball(float deltaTime) {
	if (!_fullLock) {
		if (_makingSnowball) {
			if (_timer < 12) {
				if(_bigSnowball != NULL){
					_bigSnowball->GetTransform()->addScale(0.01f);
				}
				_timer += deltaTime;
				_animate = true;
			}
			else {
				//made snowball
				//stick snowball to battler
				_animate = false;
				//add drag
				_haveBigSnowball = true;
				return true;
			}
		}
		else {
			//starting to make snowball
			std::string snowballColour = "Snowball2.png";
			if (stats.teamID == 2)
				snowballColour = "Snowball3.png";
			float radians = GetComponent<Transform*>()->getRotation() * M_PI / 180;
			_bigSnowball = new Snowball(this, 0, radians, snowballColour);
			_timer = 0;
			_makingSnowball = true;
		}
	}
	return false;
}

bool Battler::fireBigSnowball() {
	if (_haveBigSnowball) {
		if (_fullLock) {
			_throwPower += 0.3f; //ai wont care about this
			return true;
		}
		else{
			//reduce object drag
			_timer = 0;
			_fullLock = true;
			return true;
		}
	}
	return false;
}

void Battler::animateCreation() {

}

void Battler::handleCancels() {
	if (!_fullLock) {
		if (_timer < 12 && _makingSnowball) {
			//cancel snowball creation
			if(_bigSnowball != NULL){
				delete(_bigSnowball);
			}
			_makingSnowball = false;
			_timer = 0;
			_animate = false;
		}
	}
}

//-------------------------------------------------