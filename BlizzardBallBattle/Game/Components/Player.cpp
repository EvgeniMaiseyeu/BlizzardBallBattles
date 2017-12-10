#include "Player.h"
#include "HelperFunctions.h"
#include "InputManager.h"
#include "Transform.h"
#include "MatchManager.h"

Player::Player(GameObject* gameObject, SDL_Keycode left, SDL_Keycode right, SDL_Keycode up, SDL_Keycode down, SDL_Keycode shoot, SDL_Keycode shoot2, SDL_Keycode run) : Component(gameObject) {
	leftKey = left;
	rightKey = right;
	upKey = up;
	downKey = down;
	shootKey = shoot;
	runKey = run;
	shootKey2 = shoot2;
	distance = 1;
	youBattler = (Battler*)GetGameObject();
}

// Will be called every frame
void Player::OnUpdate(int timeDelta) {
	float deltaTime = (float)timeDelta / 1000.0f;

	ComputeMovement(timeDelta);

	if (youBattler->stats.teamID == 1)
	{
		MatchManager::GetInstance()->teamOneNet.TrainData(youBattler, 1.0);
	}
	else
	{
		MatchManager::GetInstance()->teamTwoNet.TrainData(youBattler, 1.0);
	}
	
	if (InputManager::GetInstance()->onKeyPressed(shootKey2)) {
		if(youBattler->GetBigSnowball()){
			youBattler->FireBigSnowball();		
		}
		else {
		//	youBattler->ThrowSnowball();
		}
		 
	}

	if (InputManager::GetInstance()->onKeyPressed(shootKey)) {
		if (!youBattler->stats.isRunning)
		{
			youBattler->ThrowSnowball();
		}
	}

	if (InputManager::GetInstance()->onKey(shootKey2)) {
		//Big snowball creating locks etc..
		youBattler->MakeBigSnowball(deltaTime);
	} 
	
	if (InputManager::GetInstance()->onKeyReleased(shootKey2)) {
		youBattler->HandleCancels();
	}

	youBattler->HandleBigThrow(deltaTime);
} 

void Player::ComputeMovement(float deltaTime) {
	float moveSpeed = youBattler->stats.moveSpeed;
	float runSpeed = youBattler->stats.runSpeed;

	bool isRunning = false;
	if (InputManager::GetInstance()->onKey(runKey)) {
		isRunning = true;
	}

	float x = 0;
	float y = 0;

	if (InputManager::GetInstance()->onKey(downKey)) {
		y -= isRunning ? runSpeed : moveSpeed;
	}
	
	if (InputManager::GetInstance()->onKey(rightKey)) {
		x += isRunning ? runSpeed : moveSpeed;
	}

	if (InputManager::GetInstance()->onKey(upKey)) {
		y += isRunning ? runSpeed : moveSpeed;
	}

	if (InputManager::GetInstance()->onKey(leftKey)) {
		x -= isRunning ? runSpeed : moveSpeed;
	}
	
	if (youBattler->InIceZone(youBattler->GetTransform())) {
		Vector2 *v = youBattler->GetVelocity();
		float prevX = v->getX();
		float prevY = v->getY();

		x = max(-isRunning ? runSpeed : moveSpeed, min(isRunning ? runSpeed : moveSpeed, prevX + (x / 20)));
		y = max(-isRunning ? runSpeed : moveSpeed, min(isRunning ? runSpeed : moveSpeed, prevY + (y / 20)));
	}

	youBattler->Move(x, y, isRunning);
} 
