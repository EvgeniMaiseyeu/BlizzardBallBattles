#include "Transform.h"
#include "HelperFunctions.h"
#include "MessageManager.h"
#include "AI.h"
#include "NetworkingManager.h"
#include "SpriteRendererManager.h"
#include "PhysicsManager.h"
#include "MatchManager.h"
#include "AudioManager.h"
#include "UserDefinedRenderLayers.h"
#include "Battler.h"
#include "Snowball.h"
#include "GameManager.h"
#include "GameScene.h"
#include "SceneManager.h"

void ReceivedFireSnowball(std::map<std::string, void*> payload) {
	Battler* self = (Battler*)payload["this"];
	std::string snowballID = (*(std::string*)payload["fireNetworkID"]);
	
	self->ThrowSnowball(snowballID);
}

Battler::Battler(int team, std::string textureFileName, std::string networkingID, bool isSender) : ComplexSprite(GenerateSpriteInfo(team), 0.0f, 0.0f)
{
	this->networkingID = networkingID;
	this->isSender = isSender;
	if (!isSender) {
		fireEventID = MessageManager::Subscribe(networkingID + "|FIRE", ReceivedFireSnowball, this);
	}
	InitStats(team);
	GetComponent<SpriteRenderer*> ()->SetLayer (RENDER_LAYER_SHADOWABLE);
	_transform = GetTransform();
}

Battler::Battler(int team, std::string textureFileName) : ComplexSprite(GenerateSpriteInfo(team), 0.0f, 0.0f)
{
	this->isSender = false;
	this->networkingID = -1;
	InitStats(team);
	GetComponent<SpriteRenderer*>()->SetLayer(RENDER_LAYER_SHADOWABLE);
	_transform = GetTransform();
}

void Battler::InitStats(int team)
{
	_physics = new Physics(this);
	AddComponent<Physics*>(_physics);
	stats.teamID = team;
	stats.moveSpeed = 2;
	stats.runSpeed = stats.moveSpeed * 2.5;
	stats.fireSpeedInterval = 1;
	stats.isPlayer = false;
	stats.hitpoints = 1;
	stats.isattached = false;
	_throwPower = 5;
	_throwDistance = 25;
	_destination = 4;
	_maxDestination = 70;
	_smallThrowPower = 15;
	_canFire = false;
}

void Battler::UpdateSprite(int ticks) {
	int currentSprite = GetCurrentSprite();
	bool isThrowing = currentSprite == SPRITE_THROW_BIG || currentSprite == SPRITE_THROW_SMALL || currentSprite == SPRITE_PICKUP_SMALL;
	
	if (_fullLock) {
		ChangeSprite(SPRITE_SPIN_BIG);
		SetFPS(_throwPower);
	} else if (!isThrowing) {
		if (_makingSnowball) {
			ChangeSprite(SPRITE_BUILD_BIG);
			SetFPS(16);
		}else if (_physics->getVelocity()->getMagnitude() > 0.5f) {
			ChangeSprite(SPRITE_WALK);
			SetFPS(_physics->getVelocity()->getMagnitude() * 10);
		}
		else {
			ChangeSprite(SPRITE_IDLE);
			SetFPS(8);
		}
	}

	
	UpdateFrames(ticks);
}

void Battler::OnUpdate(int ticks)
{
	float deltaTime = (float)ticks / 1000.0f;

	if (InIceZone(_transform))
	{
		_physics->setVelDrag(0.98);
	}
	else
	{
		_physics->setVelDrag(0.9);
	}
	CheckAndSetBounds(_transform, _physics->getVelocity());

	UpdateThrowTimer(deltaTime);
	UpdateAttachedSnowBalls(deltaTime);
	UpdateSprite(ticks);

	Transform *t = GetTransform();
	if (t != nullptr && t != NULL) {
		if (!_haveBigSnowball && !_fullLock && !_makingSnowball) {
			float maxAngle = stats.teamID == 1 ? 30.0f : -30.0f;
			float power = _physics->getVelocity()->getMagnitude();
			Vector2 vec(*_physics->getVelocity());
			vec.normalize();
			float powerMult = 1.0f;
			if (power < 1.0f) {
				powerMult = power;
			}
			float angle = maxAngle * vec.getY() * powerMult;

			if (power == 0.0f || abs(vec.getY()) < 0.025f) {
				angle = 0.0f;
			}
			angle += stats.teamID == 2 ? 180.0f : 0.0f;
			t->setRotation(angle);
		}
	}
}

bool Battler::Move(float x, float y, bool isRunning, bool forces)

{
	stats.isRunning = isRunning;
	if (!CheckAndSetBounds(_transform, new Vector2(x, y)))
	{
		return false;
	}

	_physics->setApplyingForce(forces);

	if (!_fullLock && !_makingSnowball) {
		Transform *t = GetTransform();
		Vector2 *v = new Vector2(x, y);
		_physics->setVelocity(v);
		float snowdrag = _physics->getSnowDrag();
		float drag = _physics->getDrag();
		if (_bigSnowball != nullptr && attached) {
			Vector2 *v = new Vector2(x, y);
			Physics* physics = _bigSnowball->GetComponent<Physics*>();
			physics->setDrag(drag);
			physics->setSnowDrag(snowdrag);
			physics->setVelocity(v);
		}
        return true;
    }
    else {
		if (_bigSnowball != nullptr && attached) {
			Vector2 *v = new Vector2(0,0);
			Physics* physics = _bigSnowball->GetComponent<Physics*>();
			physics->setVelocity(v);
		}
    }

	return false;
}

Vector2 *Battler::GetVelocity() {
	return _physics->getVelocity();
}

bool Battler::ThrowSnowball(std::string networkID)
{
	if (!canFire)
		return false;

	ChangeSprite(SPRITE_THROW_SMALL, SPRITE_IDLE);
	SetFPS(20);

	std::string netID = (isSender ? std::to_string(rand ()) : networkID);
	std::cout << "ANOTHER ID: " << netID << std::endl;
	if (isSender) {
		std::map<std::string, std::string> payload;
		payload["fireNetworkID"] = netID;
		NetworkingManager::GetInstance()->PrepareMessageForSending(networkingID + "|FIRE", payload);
	}

	float radians = GetComponent<Transform*>()->getRotation() * M_PI / 180;

	std::string snowballColour = "Snowball2.png";
	if (stats.teamID == 2)
		snowballColour = "Snowball3.png";

	Snowball* snowball = new Snowball(this, 5, radians, snowballColour, 30, netID, isSender);
	canFire = false;
	return true;

	//parabolic     y = y0+Vyt + 1/2 gt2
		// y=a(x–h)2+k
		// y = ax2 + bx+ c

		//
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

void Battler::UpdateAttachedSnowBalls(float deltaTimer) {
	for (int i = 0; i < attachedSnowballs.size(); i++) {
		attachedSnowballs[i]->GetTransform()->setX(attachedSnowballs[i]->getLockedOffsetX() + this->GetTransform()->getX());
		attachedSnowballs[i]->GetTransform()->setY(attachedSnowballs[i]->getLockedOffsetY() + this->GetTransform()->getY());
	}
}

bool Battler::DealtDamage(int damage)
{
	AudioManager::GetInstance()->PlaySEFhit("./Game/Assets/hit.wav", 1);
	bool isattached = false;
	stats.hitpoints -= damage;
	_physics->setSnowDrag(_physics->getSnowDrag()* 0.7);
	if (stats.hitpoints <= 0)
	{
		Die();
		return true;
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

	return false;
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
	GameObject* snowman = new GameObject(false);
	snowman->AddComponent<SpriteRenderer*>(new SpriteRenderer(snowman));
	SpriteRenderer* spriteRenderer = snowman->GetComponent<SpriteRenderer*>();
	GLuint textureTileSet = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/BackgroundTileSet.png"));
	spriteRenderer->SetActiveSprite((ISprite*)new SpriteSheet(textureTileSet, 8, 4, 0,static_cast<int>(TileIndex::Snow_Center_Alt4_Snowman)));
	spriteRenderer->SetActiveShader(Shader::GetShader(SHADER_SPRITESHEET));
	spriteRenderer->SetLayer(RENDER_LAYER_SHADOWABLE);
	snowman->GetTransform()->setPosition(GetTransform()->getX(), GetTransform()->getY(), GetTransform()->getZ());
	snowman->GetTransform()->setRotation(GetTransform()->getRotation());

	dynamic_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene())->thingsToClear.push_back(snowman);

	dying = true;

	if (isSender) {
		std::map<std::string, std::string> payload;
		NetworkingManager::GetInstance ()->PrepareMessageForSending (networkingID + "|DESTROYBATTLER", payload);
	} else {
		MessageManager::UnSubscribe (networkingID + "|FIRE", fireEventID);
	}

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
		for (int i = 0; i < attachedSnowballs.size(); i++) {
			Destroy(attachedSnowballs[i]);
		}
		MatchManager::GetInstance()->UnRegisterCharacter(this);
	}

	Destroy(this);
}

ComplexSpriteinfo* Battler::GenerateSpriteInfo(int team) {
	ComplexSpriteinfo* info = new ComplexSpriteinfo();
	if (team == 1) {
		info->AddInfo("Character_IdleSheet.png", 8, 1);
		info->AddInfo("Character_MoveSheet.png", 8, 1);
		info->AddInfo("Character_ThrowSmallSheet.png", 8, 1);
		info->AddInfo("Character_ThrowBigSheet.png", 8, 1);
		info->AddInfo("Character_BuildBigSheet.png", 8, 1);
		info->AddInfo("Character_SpinBigSheet.png", 8, 1);
		info->AddInfo("Character_PickupSmallSheet.png", 8, 1);
	} else {
		info->AddInfo("Character2_IdleSheet.png", 8, 1);
		info->AddInfo("Character2_MoveSheet.png", 8, 1);
		info->AddInfo("Character2_ThrowSmallSheet.png", 8, 1);
		info->AddInfo("Character2_ThrowBigSheet.png", 8, 1);
		info->AddInfo("Character2_BuildBigSheet.png", 8, 1);
		info->AddInfo("Character2_SpinBigSheet.png", 8, 1);
		info->AddInfo("Character2_PickupSmallSheet.png", 8, 1);
	}
	
	return info;
}

void Battler::LockToBattler(Snowball* sb) { 
	attachedSnowballs.push_back(sb);
	sb->setLockedOffsetX(sb->GetTransform()->getX() - this->GetTransform()->getX());
	sb->setLockedOffsetY(sb->GetTransform()->getY() - this->GetTransform()->getY());
}

void Battler::Unlock() {
	//
}


//------------------------------------------------------
//BIG SNOWBALL METHODS
//------------------------------------------------------

//should be called every update for each player/ai on screen

void Battler::HandleBigThrow(float deltaTime) {
	if (_fullLock && _timer < 1.5)
		_timer += deltaTime;
	else if (_fullLock && _timer > 1.5) {
		//launch snowball
		//Unlock();
		ChangeSprite(SPRITE_THROW_BIG, SPRITE_IDLE);
		SetFPS(30);

		attached = false;
		_bigSnowball->setHeld(false);
		_bigSnowball->SetDistanceGoal(_throwDistance);

		float radians = GetComponent<Transform*>()->getRotation() * M_PI / 180;
		Vector2* velocity = new Vector2(1, 0);
		velocity = *velocity * _throwPower;
		velocity->rotateVector(radians);
		_bigSnowball->GetComponent<Physics*>()->setVelocity(velocity);
		_haveBigSnowball = false;
		_fullLock = false;
		_throwDistance = 25;
		_throwPower = 5;
	}
}

bool Battler::MakeBigSnowball(float deltaTime, std::string networkID) {
	if (!_fullLock && !_haveBigSnowball) {
		if (_makingSnowball) {
			if (_timer < 2) {
				if(_bigSnowball != NULL && _bigSnowball->GetTransform() != nullptr){
					_bigSnowball->GetTransform()->addScale(0.01f);
				}
				_timer += deltaTime;
				_animate = true;
			}
			else {
				//made snowball
				_makingSnowball = false;
				attached = true;
				//LockToBattler(_bigSnowball);
				_animate = false;
				_physics->setDrag(0.4f);
				_haveBigSnowball = true;
		

				return true;
			}
		}
		else {
			//starting to make snowball
			std::string snowballColour = "Snowball2.png";
			if (stats.teamID == 2)
				snowballColour = "Snowball3.png";
			float radians = GetComponent<Transform*>()->getRotation() * M_PI / 180 / 2;
			std::string netID = (isSender ? std::to_string (rand ()) : networkID);
			if (isSender) {
				std::map<std::string, std::string> payload;
				payload["fireNetworkID"] = netID;
				NetworkingManager::GetInstance ()->PrepareMessageForSending (networkingID + "|FIRE", payload);
			}
			_bigSnowball = new Snowball(this, 0, radians, snowballColour, 0, netID, isSender);
			_bigSnowball->setBigSnowBall(true);
			_bigSnowball->setHeld(true);
			if(this->stats.teamID == 1)
				_bigSnowball->GetTransform()->addX(0.7f);
			else
				_bigSnowball->GetTransform()->addX(-0.7f);
			_bigSnowball->GetTransform()->setZ(-1);
		
			_timer = 0;
			_makingSnowball = true;
		}
	}
	return false;
}

bool Battler::FireBigSnowball() {
	if (_haveBigSnowball) {
		if (_fullLock) {
			_throwDistance += 1.0f; //ai wont care about this
			_throwPower += 1.0f; //ai wont care about this
			return true;
		}
		else{
			_physics->setDrag(1);
			_timer = 0;
			_fullLock = true;
			return true;
		}
	}
	return false;
}

bool Battler::GetBigSnowball() {
	return _haveBigSnowball;
}

void Battler::HandleCancels() {
	if (!_fullLock) {
		if (_timer < 2 && _makingSnowball) {
			//cancel snowball creation
			if (_bigSnowball != NULL) {
				_bigSnowball->DestructSnowball();
				_bigSnowball = NULL;
			}
			_makingSnowball = false;
			_timer = 0;
			_animate = false;
		}
	}
}
void Battler::AnimateCreation() {

}


//------------------------------------------------------
//SMALL SNOWBALL METHODS
//------------------------------------------------------

//should be called every update for each player/ai on screen

void Battler::HandleSmallThrow(float deltaTime)
{
	if (_canFire) {
		ChangeSprite(SPRITE_THROW_SMALL, SPRITE_IDLE);
		SetFPS(20);
		_smallSnowball->setHeld(false);
		_smallSnowball->SetDestination(_destination);
		float radians = GetComponent<Transform*>()->getRotation() * M_PI / 180;
		Vector2* velocity = new Vector2(1, 0);
		velocity = *velocity * _smallThrowPower;
		velocity->rotateVector(radians);
		_smallSnowball->GetComponent<Physics*>()->setVelocity(velocity);
		_haveSmallSnowball = false;
		_smallSnowball->setPower(_smallThrowPower);
		_canFire = false;
		_destination = 4;
	}
}

bool Battler::MakeSmallSnowball(std::string networkID) {

	//starting to make snowball
	std::string snowballColour = "Snowball2.png";
	if (stats.teamID == 2)
		snowballColour = "Snowball3.png";
	ChangeSprite(SPRITE_PICKUP_SMALL, SPRITE_IDLE);
	SetFPS(20);
	float radians = GetComponent<Transform*>()->getRotation() * M_PI / 180 / 2; 
	std::string netID = (isSender ? std::to_string (rand ()) : networkID);
	if (isSender) {
		std::map<std::string, std::string> payload;
		payload["fireNetworkID"] = netID;
		NetworkingManager::GetInstance ()->PrepareMessageForSending (networkingID + "|FIRE", payload);
	}
	_smallSnowball = new Snowball(this, 0, radians, snowballColour, 0, netID, isSender);

	if (this->stats.teamID == 1)
		_smallSnowball->GetTransform()->addY(-0.5f);
	else
		_smallSnowball->GetTransform()->addY(0.5f);
	_smallSnowball->GetTransform()->setZ(-1);

	_haveSmallSnowball = true;
	_smallSnowball->setHeld(true);
	return false;
}

bool Battler::FireSmallSnowball() {
	if (_haveSmallSnowball) {
		_destination += 0.3f; //ai wont care about this
		if (_destination > _maxDestination) {
			_destination = _maxDestination;
		}
	}

	return false;
}

void Battler::setCanFire() {
	if(_haveSmallSnowball)
		_canFire = true;
}

bool Battler::GetSmallSnowball() {
	return _haveSmallSnowball;

}

//-------------------------------------------------

bool Battler::CheckAndSetBounds(Transform *pos, Vector2 *move)
{
	float multiplier = stats.isRunning ? 2.5: 1.0;

	float xMin = (-getGameWidth() / 2) - 2;
	float xMax = (getGameWidth() / 2) + 2;
	float yMax = (getGameHeight() / 2) + 1.25;
	float yMin = -(getGameHeight() / 2) - 1;

	float team1Bounds = (xMin + ((xMax - xMin) / 2)) + 7;
	float team2Bounds = (xMin + ((xMax - xMin) / 2)) - 6;

	bool inBounds = true;

	float xVelocity = move->getX();
	float yVelocity = move->getY();

	xVelocity /= multiplier;
	yVelocity /= multiplier;

	unique_ptr<Vector2> newPos(new Vector2(pos->getX() + xVelocity, pos->getY() + yVelocity));

	if (newPos->getX() <= (stats.teamID == 2 ? team2Bounds : xMin)) {
		if (move->getX() < 0)
			move->setX(0);
		inBounds = false;
	}

	if (newPos->getX() >= (stats.teamID == 1 ? team1Bounds : xMax)) {
		if (move->getX() > 0)
			move->setX(0);
		inBounds = false;
	}

	if (newPos->getY() <= yMin) {
		if (move->getY() < 0)
			move->setY(0);
		inBounds = false;
	}

	if (newPos->getY() >= yMax) {
		if (move->getY() > 0)
			move->setY(0);
		inBounds = false;
	}
	return inBounds;
}

bool Battler::InIceZone(Transform *t) {
	if (t != NULL && t != nullptr) {
		if (GameScene* scene = GameScene::GetCurrent()) {
			return scene->isInIceZone(t->getX(), t->getY());
		}
	}
	return false;
}

//bool Battler::ApplyIceSliding(Vector2 *v) {
//	if (InIceZone(GetTransform())) {
//		v->setX(v->getX() * 0.99f);
//		v->setY(v->getY() * 0.99f);
//		return true;
//	}
//	return false;
//}
