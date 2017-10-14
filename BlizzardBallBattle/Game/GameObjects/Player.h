#pragma once

#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Transform.h"
#include "InputManager.h"

class Player : public GameObject {
private:

public:
	Player(Shader* shader, GLuint textureBufferID);
	void PressedLeft();
	void PressedRight();
	void PressedUp();
	void PressedDown();
	void PressedAway();
	void Update(float timeDelta);
};