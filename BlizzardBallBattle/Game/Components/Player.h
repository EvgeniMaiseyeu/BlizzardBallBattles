#pragma once

#include "GameObject.h"
#include "Transform.h"
#include "InputManager.h"
#include "GLHeaders.h"
#include "Shader.h"
#include "Battler.h"

class Player : public Component {
private:
	SDL_Keycode leftKey;
	SDL_Keycode rightKey;
	SDL_Keycode upKey;
	SDL_Keycode downKey;
	//SDL_Keycode shootKey;
	float distance;
	Battler* youBattler;
	float center;

	
public:
	Player(GameObject* gameObject, SDL_Keycode left,  SDL_Keycode right, SDL_Keycode up, SDL_Keycode down);
	//void setKeys(leftKey, rightKey, downKey, upKey)
	void PressedLeft();
	void PressedRight();
	void PressedUp();
	void PressedDown();
	//void PressedShoot();
	virtual void Update(int ticks);
};
