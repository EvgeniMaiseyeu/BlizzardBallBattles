#pragma once

#include "GameObject.h"
#include "Component.h"

class Collider : public Component {
private:
	GameObject* _colliderObj;
	float _radius;
	bool _collision;
public:
	Collider(GameObject* gameObject, float radius);
	bool DoesCollide(GameObject* other);
	float getRadius();
	void setRadius(float radius);

	bool collisionDetected();
	void setCollision(bool collision);

	GameObject* getColliderObj();
	void setColliderObj(GameObject* collider);

	void OnStart() {};
	void OnUpdate(int ticks) {};
	void OnEnd() {};
};