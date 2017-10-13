#pragma once

#include "GameObject.h"
#include "SpriteRenderer.h"

class Player : public GameObject {
private:

public:
	Player(Shader* shader, GLuint textureBufferID);
	void PressedLeft();
	void PressedRight();
	void PressedUp();
	void PressedDown();
	void PressedAway();
};