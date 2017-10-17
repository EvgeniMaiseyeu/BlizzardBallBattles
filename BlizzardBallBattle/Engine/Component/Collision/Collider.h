#pragma once

#include "GameObject.h"
#include "Component.h"

class Collider : public Component {
private:

public:
	Collider(GameObject* gameObject);
	bool DoesCollide(GameObject* other);
};