#pragma once

#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Transform.h"
#include "InputManager.h"
#include "GLHeaders.h"

class Player : public GameObject {
private:
	SDL_Keycode leftKey;
	SDL_Keycode rightKey;
	SDL_Keycode upKey;
	SDL_Keycode downKey;
	
public:
	Player(Shader* shader, GLuint textureBufferID, SDL_Keycode left, SDL_Keycode right, SDL_Keycode up, SDL_Keycode down);
	//void setKeys(leftKey, rightKey, downKey, upKey)
	void PressedLeft();
	void PressedRight();
	void PressedUp();
	void PressedDown();
	//void PressedLeft1();
	//void PressedRight1();
	//void PressedUp1();
	//void PressedDown1();
	void Update(float timeDelta);
};

