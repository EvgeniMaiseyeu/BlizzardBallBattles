#include "Player.h"
#include "HelperFunctions.h"

Player::Player(Shader* shader, GLuint textureBufferID, SDL_Keycode left, SDL_Keycode right, SDL_Keycode up, SDL_Keycode down) {
	leftKey = left;
	rightKey = right;
	upKey = up;
	downKey = down;
	AddComponent<SpriteRenderer*>(new SpriteRenderer(this));
	SpriteRenderer* renderer = (SpriteRenderer*)GetComponent<SpriteRenderer*>();
	renderer->SetActiveShader(shader);
	renderer->SetActiveTexture(textureBufferID);

	
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

	//inputManager = InputManager::GetInstance();
	//if (inputManager->onKey(SDLK_k)) {
	//	PressedDown1();
	//}
	//inputManager = InputManager::GetInstance();
	//if (inputManager->onKey(SDLK_l)) {
	//	PressedRight1();
	//}
	//
	//inputManager = InputManager::GetInstance();
	//if (inputManager->onKey(SDLK_i)) {
	//	PressedUp1();
	//}
	//
	//inputManager = InputManager::GetInstance();
	//if (inputManager->onKey(SDLK_j)) {
	//	PressedLeft1();
	//}
}


void Player::PressedDown() {
	if (GetComponent<Transform*>()->getY() + -0.2f < -getGameHeight()/2)
	{
		return;
	}

	Transform* transform = (Transform*)GetComponent<Transform*>();
	transform->addTranslation(0, -0.2f);
}

void Player::PressedRight() {
	if (GetComponent<Transform*>()->getX() + 0.2f > GAME_WIDTH / 2)
	{
		return;
	}
	Transform* transform = (Transform*)GetComponent<Transform*>();
	transform->addTranslation(0.2f, 0);


	

}

void Player::PressedUp() {
	if (GetComponent<Transform*>()->getY() + 0.2f > getGameHeight() / 2)
	{
		return;
	}
	Transform* transform = (Transform*)GetComponent<Transform*>();
	transform->addTranslation(0, 0.2f);
	

}

void Player::PressedLeft() {
	if (GetComponent<Transform*>()->getX() + -0.2f < - GAME_WIDTH / 2)
	{
		return;
	}
	Transform* transform = (Transform*)GetComponent<Transform*>();
	transform->addTranslation(-0.2f, 0);
	

}
/*void Player::PressedDown1() {
	Transform* transform = (Transform*)GetComponent<Transform*>();
	transform->addTranslation(0, -0.2f);
}

void Player::PressedRight1() {
	Transform* transform = (Transform*)GetComponent<Transform*>();
	transform->addTranslation(0.2f, 0);


}

void Player::PressedUp1() {
	Transform* transform = (Transform*)GetComponent<Transform*>();
	transform->addTranslation(0, 0.2f);


}

void Player::PressedLeft1() {
	Transform* transform = (Transform*)GetComponent<Transform*>();
	transform->addTranslation(-0.2f, 0);

	
}*/

