#include "Collider.h"
#include "Transform.h"
#include <math.h>

Collider::Collider(GameObject* gameObject, float radius) : Component(gameObject) , _radius(radius){
	_collision = false;
}

bool Collider::collisionDetected() {
	return _collision;
}

void Collider::setCollision(bool collision) {
	_collision = collision;
}

bool Collider::DoesCollide(GameObject* other) {
	Transform* myTrans = gameObject->GetComponent<Transform*>();
	Transform* otherTrans = other->GetComponent<Transform*>();

	float a = myTrans->getX() - otherTrans->getX();
	float b = myTrans->getY() - otherTrans->getY();
	float c = std::sqrtf(a * a + b * b);
	float myRad = myTrans->getScale() / 2.0f;
	float otherRad = otherTrans->getScale() / 2.0f;

	return c <= myRad + otherRad;
}

GameObject* Collider::getColliderObj() {
	return _colliderObj;
}

void Collider::setColliderObj(GameObject* collider) {
	_colliderObj = collider;
}

float Collider::getRadius() {
	return _radius;
}

void Collider::setRadius(float radius) {
	_radius = radius;
}
