#include "Player.h"
#include "InputManager.h"
#include "Battler.h"
#include "Transform.h"

Player::Player(GameObject* gameObject) : Component(gameObject) {
}

//Will be called every frame
void Player::Update(int timeDelta) {
	InputManager* inputManager = InputManager::GetInstance();
	if (inputManager->onKey(SDLK_s)) {
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
	//Transform* transform = GetGameObject()->GetComponent<Transform*>();
	//transform->addTranslation(0, -0.2f);

	//Vector2* move = &Vector2(0, -0.2f);
	Battler* myBattler = (Battler*)GetGameObject();
	myBattler->Move(0, -0.2f);
}

void Player::PressedRight() {
	//Transform* transform = GetGameObject()->GetComponent<Transform*>();
	//transform->addTranslation(0.2f, 0);

	Battler* myBattler = (Battler*)GetGameObject();
	myBattler->Move(0.2f, 0);
}

void Player::PressedUp() {
	//Transform* transform = GetGameObject()->GetComponent<Transform*>();
	//transform->addTranslation(0, 0.2f);

	Battler* myBattler = (Battler*)GetGameObject();
	myBattler->Move(0, 0.2f);
}

void Player::PressedLeft() {
	//Transform* transform = GetGameObject()->GetComponent<Transform*>();
	//transform->addTranslation(-0.2f, 0);

	Battler* myBattler = (Battler*)GetGameObject();
	myBattler->Move(-0.2f, 0);
}

