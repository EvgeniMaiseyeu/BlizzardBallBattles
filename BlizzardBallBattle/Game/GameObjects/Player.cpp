#include "Player.h"

Player::Player() : Component(gameObject) {
	
}

//Will be called every frame
void Player::Update(float timeDelta) {
	InputManager* inputManager = InputManager::GetInstance();
	if (inputManager->onKey(SDLK_a)) {
		PressedDown();
	}
	inputManager = InputManager::GetInstance();
	if (inputManager->onKey(SDLK_d)) {
		PressedRight();
	}

	inputManager = InputManager::GetInstance();
	if (inputManager->onKey(SDLK_w)) {
		PressedUp();
	}

	inputManager = InputManager::GetInstance();
	if (inputManager->onKey(SDLK_a)) {
		PressedLeft();
	}
}

void Player::PressedDown() {
	//Transform* transform = (Transform*)GetComponent<Transform*>();
	//transform->addTranslation(0, -0.2f);
}

void Player::PressedRight() {
	//Transform* transform = (Transform*)GetComponent<Transform*>();
	//transform->addTranslation(0.2f, 0);
	

}

void Player::PressedUp() {
	//Transform* transform = (Transform*)GetComponent<Transform*>();
	//transform->addTranslation(0, 0.2f);
	

}

void Player::PressedLeft() {
	//Transform* transform = (Transform*)GetComponent<Transform*>();
	//transform->addTranslation(-0.2f, 0);
	

}

