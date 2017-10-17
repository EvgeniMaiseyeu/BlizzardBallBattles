
#include "Physics.h"	

Physics::Physics(GameObject* gameObject) : Component(gameObject) {
	_velocity = new Vector2(0, 0);
	_aVelocity = new Vector2(0, 0);
}

void Physics::setVelocity(Vector2* value) {
	_velocity = value;
}

Vector2* Physics::getVelocity() {
	return _velocity;
}

void Physics::setAngularVelocity(Vector2* value) {
	_aVelocity = value;
}

Vector2* Physics::getAngularVelocity() {
	return _aVelocity;
}

void Physics::setSnowDrag(float value) {
	_snowDrag = value;
}

float Physics::getSnowDrag() {
	return _snowDrag;
}

void Physics::setDrag(float value) {
	_drag = value;
}

float Physics::getDrag() {
	return _drag;
}

void update() {
	
}

Physics::~Physics() {
	if (_velocity != NULL)
		delete(_velocity);
	if (_aVelocity != NULL)
		delete(_aVelocity);
}