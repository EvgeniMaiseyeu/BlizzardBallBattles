#pragma once

#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Transform.h"
#include "InputManager.h"

class Player : public Component {
private:

public:
	Player();
	void PressedLeft();
	void PressedRight();
	void PressedUp();
	void PressedDown();
	void PressedAway();
	void Update(float timeDelta);
};