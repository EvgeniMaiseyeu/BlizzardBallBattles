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

	if (InputManager::GetInstance()->onKey(downKey)) {
		PressedDown(moveSpeed);
	}
	
	if (InputManager::GetInstance()->onKey(rightKey)) {
		PressedRight(moveSpeed);
	}

	if (InputManager::GetInstance()->onKey(upKey)) {
		PressedUp(moveSpeed);
	}

	if (InputManager::GetInstance()->onKey(leftKey)) {
		PressedLeft(moveSpeed);
	}

	if (InputManager::GetInstance()->onKeyReleased(downKey)) {
		PressedDown(0);
	}

	if (InputManager::GetInstance()->onKeyReleased(rightKey)) {
		PressedRight(0);
	}

	if (InputManager::GetInstance()->onKeyReleased(upKey)) {
		PressedUp(0);
	}

	if (InputManager::GetInstance()->onKeyReleased(leftKey)) {
		PressedLeft(0);
	}
	
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

void Player::PressedDown(float moveSpeed) {
	if (GetGameObject()->GetTransform()->getY() + -moveSpeed < -getGameHeight()/2)
	{
		return;
	}
	
	youBattler->Move(0, -moveSpeed);
//	youBattler->setSnowDrag(1);
}

void Player::PressedRight(float moveSpeed) {
	if (youBattler->stats.teamID == 1 && GetGameObject()->GetTransform()->getX() > -4.0f)
	{
		return;
	}
	else if (GetGameObject()->GetTransform()->getX() + moveSpeed > GAME_WIDTH / 2)
	{
		return;
	}

	youBattler->Move(moveSpeed, 0);
}

void Player::PressedUp(float moveSpeed) {
	if (GetGameObject()->GetTransform()->getY() + moveSpeed > getGameHeight() / 2)
	{
		return;
	}
	
	youBattler->Move(0, moveSpeed);
}

void Player::PressedLeft(float moveSpeed) {
	if (youBattler->stats.teamID == 2 && GetGameObject()->GetTransform()->getX() < 4.0f)
	{
		return;
	}
	else if (GetGameObject()->GetTransform()->getX() + -moveSpeed < -GAME_WIDTH / 2)
	{
		return;
	}	

	youBattler->Move(-moveSpeed, 0);
}