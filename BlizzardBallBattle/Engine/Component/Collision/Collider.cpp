#include "Collider.h"
#include "Transform.h"
#include <math.h>

Collider::Collider(GameObject* gameObject) : Component(gameObject) {

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