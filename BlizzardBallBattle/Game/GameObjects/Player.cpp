#include "Player.h"
#include "HelperFunctions.h"

Player::Player(Shader* shader, GLuint textureBufferID, SDL_Keycode left, SDL_Keycode right, SDL_Keycode up, SDL_Keycode down) {
	leftKey = left;
	rightKey = right;
	upKey = up;
	downKey = down;
	distance = 2;
	//upKey1 = up;
	//downKey1 = down;
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




	/*inputManager = InputManager::GetInstance();
	if (inputManager->onKey(downKey1)) {
		PressedDown1();
	}
	inputManager = InputManager::GetInstance();
	if (inputManager->onKey(rightKey1)) {
		PressedRight1();
	}
	
	inputManager = InputManager::GetInstance();
	if (inputManager->onKey(upKey1)) {
		PressedUp1();
	}
	
	inputManager = InputManager::GetInstance();
	if (inputManager->onKey(leftKey)) {
		PressedLeft1();
	}*/
} 


void Player::PressedDown() {
	if (GetComponent<Transform*>()->getY() + -distance < -getGameHeight()/2)
	{
		return;
	}

	
	this->GetComponent <Transform*>() ->addTranslation(0, -0.2f);
}

void Player::PressedRight() {
	if (GetComponent<Transform*>()->getX() + distance > GAME_WIDTH / 2)
	{
		return;
	}
	this->GetComponent <Transform*>()->addTranslation(0.2f, 0);
}



void Player::PressedUp() {
	if (GetComponent<Transform*>()->getY() + distance> getGameHeight() / 2)
	{
		return;
	}
	this->GetComponent <Transform*>()->addTranslation(0, 0.2f);
	

}

void Player::PressedLeft() {
	if (GetComponent<Transform*>()->getX() + -distance < - GAME_WIDTH / 2)
	{
		return;
	}
	this->GetComponent <Transform*>()->addTranslation(-0.2f, 0);
	

}


/*void Player::PressedDown1() {
	if (GetComponent<Transform*>()->getX() + -1.5f < -GAME_WIDTH / 2)
	{
		return;
	}
	this->GetComponent <Transform*>()->addTranslation( 0, -0.2f);

}

void Player::PressedRight1() {
	if (GetComponent<Transform*>()->getX() + -1.5f < -GAME_WIDTH / 2)
	{
		return;
	}
	this->GetComponent <Transform*>()->addTranslation(0.2f, 0);



}

void Player::PressedUp1() {
	if (GetComponent<Transform*>()->getX() + -1.5f < -GAME_WIDTH / 2)
	{
		return;
	}
	this->GetComponent <Transform*>()->addTranslation(0, 0.2f);


}

void Player::PressedLeft1() {
	if (GetComponent<Transform*>()->getX() + -1.5f < -GAME_WIDTH / 2)
	{
		return;
	}
	this->GetComponent <Transform*>()->addTranslation(-0.2f, 0);


	
}*/

