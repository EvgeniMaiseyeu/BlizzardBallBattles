
#include "Physics.h"	

Physics::Physics(GameObject* gameObject) : Component(gameObject) {
	_velocity = new Vector2(0, 0);
	_aVelocity = new Vector2(0, 0);
	_drag = 1;
	_snowDrag = 1;
	_velDrag = 1;
	_applyingForce = false;
	transform = gameObject->GetTransform();
}

void Physics::setVelocity(Vector2* value) {
	delete(_velocity);
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

void Physics::setApplyingForce(bool value)
{
	_applyingForce = value;
}

bool Physics::getApplyingForce()
{
	return _applyingForce;
}

void Physics::setSnowDrag(float value) {
	_snowDrag = value;
}

void Physics::addSnowDrag(float value){
	_snowDrag += value;
}

float Physics::getSnowDrag() {
	return _snowDrag;
}

void Physics::setDrag(float value) {
	_drag = value;
}

void Physics::addDrag(float value){
	_drag += value;
}

void Physics::setVelDrag(float value)
{
	_velDrag = value;
}

float Physics::getVelDrag()
{
	return _velDrag;
}

void Physics::addVelDrag(float value)
{
	_velDrag += value;
}

float Physics::getDrag() {
	return _drag;
}

void Physics::OnUpdate(int ticks) {
	if (!_applyingForce) {
		_velocity->setX(_velocity->getX() * _velDrag);
		_velocity->setY(_velocity->getY() * _velDrag);
	}
	transform->addX(_velocity->getX() * _drag * _snowDrag * ((float)ticks) / 1000);
	transform->addY(_velocity->getY() * _drag * _snowDrag * ((float)ticks) / 1000);
	//setup angular velocity
	
}

Physics::~Physics() {
	if (_velocity != NULL)
		delete(_velocity);
	if (_aVelocity != NULL)
		delete(_aVelocity);	
}