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

	Vector2 *newVector = new Vector2(0, 0);

	if (InputManager::GetInstance()->onKey(downKey)) {
		newVector->setY(-moveSpeed);
	}
	
	if (InputManager::GetInstance()->onKey(rightKey)) {
		newVector->setX(moveSpeed);
	}

	if (InputManager::GetInstance()->onKey(upKey)) {
		newVector->setY(moveSpeed);
	}

	if (InputManager::GetInstance()->onKey(leftKey)) {
		newVector->setX(-moveSpeed);
	}
	
	if (InputManager::GetInstance()->onKeyPressed(shootKey)) {
		if(youBattler->getBigSnowball()){
			youBattler->fireBigSnowball();		
		}
		else {
		//	youBattler->ThrowSnowball();
		}
		 
	}
	if (InputManager::GetInstance()->onKey(shootKey)) {
		//Big snowball creating locks etc..
		youBattler->makeBigSnowball(deltaTime);
	} 
	
	if (InputManager::GetInstance()->onKeyReleased(shootKey)) {
		youBattler->handleCancels();
	}
	if (youBattler->InIceZone(youBattler->GetTransform())) {
		Vector2 *v = youBattler->GetVelocity();

		newVector->setX(max(-moveSpeed, min(moveSpeed, v->getX() + (newVector->getX() / 20))));
		newVector->setY(max(-moveSpeed, min(moveSpeed, v->getY() + (newVector->getY() / 20))));
	}

	youBattler->Move(newVector, deltaTime);
}