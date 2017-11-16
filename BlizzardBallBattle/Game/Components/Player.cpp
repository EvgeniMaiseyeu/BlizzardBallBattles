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

	youBattler->handleBigThrow(deltaTime);

	youBattler->Move(newVector, deltaTime);

} 
