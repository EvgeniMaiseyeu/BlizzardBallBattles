#pragma once

#include "GameObject.h"
#include "Transform.h"
#include "InputManager.h"
#include "GLHeaders.h"
#include "Shader.h"

class Player : public Component {
private:
	SDL_Keycode leftKey;
	SDL_Keycode rightKey;
	SDL_Keycode upKey;
	SDL_Keycode downKey;
	float distance;

	
public:
	Player(GameObject* gameObject, SDL_Keycode left,  SDL_Keycode right, SDL_Keycode up, SDL_Keycode down);
	//void setKeys(leftKey, rightKey, downKey, upKey)
	void PressedLeft();
	void PressedRight();
	void PressedUp();
	void PressedDown();
	void Update(float timeDelta);
};
