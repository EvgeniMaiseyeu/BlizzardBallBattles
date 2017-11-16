#include "Player.h"
#include "HelperFunctions.h"
#include "InputManager.h"
#include "Transform.h"

Player::Player(GameObject* gameObject, SDL_Keycode left, SDL_Keycode right, SDL_Keycode up, SDL_Keycode down, SDL_Keycode shoot) : Component(gameObject) {
	leftKey = left;
	rightKey = right;
	upKey = up;
	downKey = down;
	shootKey = shoot;
	distance = 1;
	youBattler = (Battler*)GetGameObject();
	
}

// Will be called every frame
void Player::OnUpdate(int timeDelta) {
	float deltaTime = (float)timeDelta / 1000.0f;

	ComputeMovement(timeDelta);
	
	if (InputManager::GetInstance()->onKeyPressed(shootKey)) {
		if(!youBattler->fireBigSnowball()){
			youBattler->ThrowSnowball();
		}
		
	} else if (InputManager::GetInstance()->onKey(shootKey)) {
		//Big snowball creating locks etc..
		youBattler->makeBigSnowball(deltaTime);
	} 
	
	if (InputManager::GetInstance()->onKeyReleased(shootKey)) {
		youBattler->handleCancels();
	}

	youBattler->handleBigThrow(deltaTime);
} 

void Player::ComputeMovement(float deltaTime) {
	float moveSpeed = youBattler->stats.moveSpeed;

	float x = 0;
	float y = 0;

	if (InputManager::GetInstance()->onKey(downKey)) {
		y -= moveSpeed;
	}
	
	if (InputManager::GetInstance()->onKey(rightKey)) {
		x += moveSpeed;
	}

	if (InputManager::GetInstance()->onKey(upKey)) {
		y += moveSpeed;
	}

	if (InputManager::GetInstance()->onKey(leftKey)) {
		x -= moveSpeed;
	}
	
	if (youBattler->InIceZone(youBattler->GetTransform())) {
		Vector2 *v = youBattler->GetVelocity();
		float prevX = v->getX();
		float prevY = v->getY();

		x = max(-moveSpeed, min(moveSpeed, prevX + (x / 20)));
		y = max(-moveSpeed, min(moveSpeed, prevY + (y / 20)));
	}

	youBattler->Move(x, y, deltaTime);
}