#include "Player.h"
#include "HelperFunctions.h"
#include "InputManager.h"
#include "Battler.h"
#include "Transform.h"

Player::Player(GameObject* gameObject, SDL_Keycode left, SDL_Keycode right, SDL_Keycode up, SDL_Keycode down) : Component(gameObject) {
	leftKey = left;
	rightKey = right;
	upKey = up;
	downKey = down;
	distance = 2;
	//upKey1 = up;
	//downKey1 = down;
}

//Will be called every frame
void Player::Update(float timeDelta) {
	InputManager* inputManager = InputManager::GetInstance();
	if (inputManager->onKey(downKey)) {
		PressedDown();
	}

	inputManager = InputManager::GetInstance();
	if (inputManager->onKey(rightKey)) {
		PressedRight();
	}

	inputManager = InputManager::GetInstance();
	if (inputManager->onKey(upKey)) {
		PressedUp();
	}

	inputManager = InputManager::GetInstance();
	if (inputManager->onKey(leftKey)) {
		PressedLeft();
	}
} 


void Player::PressedDown() {
	if (GetGameObject()->GetComponent<Transform*>()->getY() + -distance < -getGameHeight()/2)
	{
		return;
	}

	
	GetGameObject()->GetComponent <Transform*>()->addTranslation(0, -0.2f);

	//Vector2* move = &Vector2(0, -0.2f);
	//Battler* myBattler = (Battler*)GetGameObject();
	//myBattler->Move(0, -0.2f);
}

void Player::PressedRight() {
	if (GetGameObject()->GetComponent<Transform*>()->getX() + distance > GAME_WIDTH / 2)
	{
		return;
	}
	GetGameObject()->GetComponent <Transform*>()->addTranslation(0.2f, 0);
}



void Player::PressedUp() {
	if (GetGameObject()->GetComponent<Transform*>()->getY() + distance> getGameHeight() / 2)
	{
		return;
	}
	GetGameObject()->GetComponent <Transform*>()->addTranslation(0, 0.2f);
}

void Player::PressedLeft() {
	if (GetGameObject()->GetComponent<Transform*>()->getX() + -distance < - GAME_WIDTH / 2)
	{
		return;
	}
	GetGameObject()->GetComponent <Transform*>()->addTranslation(-0.2f, 0);
}