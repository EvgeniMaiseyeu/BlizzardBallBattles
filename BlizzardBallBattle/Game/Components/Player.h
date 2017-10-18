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
	SDL_Keycode shootKey, shootKey1;
	float distance;
	Battler* youBattler;
	float center;
	bool PressedShoot(Battler *character);

	
public:
	Player(GameObject* gameObject, SDL_Keycode left,  SDL_Keycode right, SDL_Keycode up, SDL_Keycode down, SDL_Keycode shoot);
	//void setKeys(leftKey, rightKey, downKey, upKey)
	void PressedLeft();
	void PressedRight();
	void PressedUp();
	void PressedDown();
	void PressedShoot();
	void OnStart(){};
	void OnUpdate(int ticks);
	void OnEnd(){};
};
