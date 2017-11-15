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
	float moveSpeed = deltaTime * youBattler->stats.moveSpeed;

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

	if (InputManager::GetInstance()->onKeyPressed(shootKey)) {
		youBattler->ThrowSnowball(); 
	}
} 

void Player::PressedDown(float moveSpeed) {
	//if (GetGameObject()->GetTransform()->getY() + -moveSpeed < -getGameHeight()/2)
	//{
	//	return;
	//}
	
	youBattler->Move(0, -moveSpeed);
}

void Player::PressedRight(float moveSpeed) {
	//if (youBattler->stats.teamID == 1 && GetGameObject()->GetComponent<Transform*>()->getX() > -4.0f)
	//{
	//	return;
	//}
	//else if (GetGameObject()->GetComponent<Transform*>()->getX() + moveSpeed > GAME_WIDTH / 2)
	//{
	//	return;
	//}

	youBattler->Move(moveSpeed, 0);
}

void Player::PressedUp(float moveSpeed) {
	//if (GetGameObject()->GetComponent<Transform*>()->getY() + moveSpeed > getGameHeight() / 2)
	//{
	//	return;
	//}
	
	youBattler->Move(0, moveSpeed);
}

void Player::PressedLeft(float moveSpeed) {
	//if (youBattler->stats.teamID == 2 && GetGameObject()->GetComponent<Transform*>()->getX() < 4.0f)
	//{
	//	return;
	//}
	//else if (GetGameObject()->GetComponent<Transform*>()->getX() + -moveSpeed < -GAME_WIDTH / 2)
	//{
	//	return;
	//}

	youBattler->Move(-moveSpeed, 0);
}