#pragma once

#include "GameObject.h"
#include "Shader.h"

class Player : public Component {
private:

public:
	Player(GameObject* gameObject);
	void PressedLeft();
	void PressedRight();
	void PressedUp();
	void PressedDown();
	void PressedAway();
	virtual void Update(int ticks);
};