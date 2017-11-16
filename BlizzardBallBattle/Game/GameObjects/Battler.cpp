#include "Transform.h"
#include "HelperFunctions.h"
#include "MessageManager.h"
#include "AI.h"
#include "NetworkingManager.h"
#include "SpriteRendererManager.h"
#include "PhysicsManager.h"
#include "MatchManager.h"
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

void Battler::OnUpdate(int ticks)
{
	if (_transform == NULL)
	{
		_transform = GetTransform();
	}

	float deltaTime = (float)ticks / 1000.0f;

	UpdateThrowTimer(deltaTime);
	//if (!CheckIfInBounds(_transform->getX(), _transform->getY()))
	//{
	//	Move(0, 0);
	//}
}

void Battler::InitStats(int team)
{
	_physics = new Physics(this);
	AddComponent<Physics*>(_physics);
	stats.teamID = team;
	stats.moveSpeed = 2;
	stats.fireSpeedInterval = 1;
	stats.isPlayer = false;
	stats.hitpoints = 1;
	stats.isattached = false;
}

bool Battler::Move(float x, float y)
{
	if (CheckIfInBounds(x + _transform->getX(), y + _transform->getY()))
	{
		_physics->setVelocity(new Vector2(x, y));
		return true;
	}
	return false;
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
	bool isattached = false;
	stats.hitpoints -= damage;
	_physics->setSnowDrag(_physics->getSnowDrag()* 0.7);
	if (stats.hitpoints <= 0)
	{
		Die();
	}
	if (stats.isattached)
	{
		ThrowSnowball();

	}
	else
	{
	//	Snowball* snowball = new Snowball();
		
	//	GetGameObject()->GetTransform()->addTranslation()->Player position;
		
	}
	//return true;

}

/*bool Battler::IsAttached()
{
	if (stats.isattached)
	{
		find.Player();
	}
	else
	{
		Snowball* snowball = new Snowball();
		GetGameObject() -> GetTransform()->addTranslation()->Player position;
	}
	return true;
}*/

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
void Battler::HandleBigThrow(float deltaTime) {
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
bool Battler::MakeBigSnowball(float deltaTime) {
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

bool Battler::FireBigSnowball() {
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

void Battler::AnimateCreation() {

}

void Battler::HandleCancels() {
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

bool Battler::CheckIfInBounds(float x, float y)
{
	float mapXMax = getGameWidth() / 2;
	float mapYMax = getGameHeight() / 2;
	float mapXMin = getGameWidth() / 6;
	float mapYMin = -mapYMax;

	//if (GetGameObject()->GetComponent<Transform*>()->getY() + moveSpeed > getGameHeight() / 2)
	//{
	//	return;
	//}

	if (stats.teamID == 1)
	{
		mapXMin = -mapXMin;
		mapXMax = -mapXMax;
	}

	if (x < mapXMin || x > mapXMax)
	{
		return false;
	}
	else if (y < mapYMin || y > mapYMax)
	{
		return false;
	}

	return true;
}

