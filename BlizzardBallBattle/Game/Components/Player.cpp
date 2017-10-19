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

//Will be called every frame
void Player::OnUpdate(int timeDelta) {
	InputManager* inputManager = InputManager::GetInstance();
	if (inputManager->onKey(downKey)) {
		PressedDown();
	}

	
	if (inputManager->onKey(rightKey)) {
		PressedRight();
	}

	if (inputManager->onKey(upKey)) {
		PressedUp();
	}


	if (inputManager->onKey(leftKey)) {
		PressedLeft();
	}

	
	if (inputManager->onKey(shootKey)) {
		youBattler->ThrowSnowball(); 
	}
	
} 


void Player::PressedDown() {
	if (GetGameObject()->GetComponent<Transform*>()->getY() + -distance < -getGameHeight()/2)
	{
		return;
	}

	
	youBattler->Move(0, -0.2f);
	
	

	//Vector2* move = &Vector2(0, -0.2f);
	//Battler* myBattler = (Battler*)GetGameObject();
	//myBattler->Move(0, -0.2f);
}

void Player::PressedRight() {
	if (GetGameObject()->GetComponent<Transform*>()->getX() + distance > GAME_WIDTH / 2)
	{
		return;
	}
	


	if (youBattler->stats.teamID == 1 && GetGameObject()->GetComponent<Transform*>()->getX() > -4.0f)

	{
		return;

	}

	youBattler->Move(0.2f, 0);
	GetGameObject()->GetComponent <Transform*>()->addRotation(15);
	

	
}

void Player::PressedUp() {
	if (GetGameObject()->GetComponent<Transform*>()->getY() + distance> getGameHeight() / 2)
	{
		return;
	}
	
	youBattler->Move(0, 0.2f);
	
	youBattler->Move(0, 0.2f);
	

}

void Player::PressedLeft() {
	if (GetGameObject()->GetComponent<Transform*>()->getX() + -distance < - GAME_WIDTH / 2)
	{
		return;
	}



	if (youBattler->stats.teamID == 2 && GetGameObject()->GetComponent<Transform*>()->getX() <4.0f)

	{
		return;
	}
	youBattler->Move(-0.2f, 0);
	GetGameObject()->GetComponent <Transform*>()->addRotation(15);
	
}