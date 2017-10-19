
#include "PhysicsManager.h"
#include <stdio.h>
#include <cmath>
#include "SceneManager.h"
#include <algorithm>

PhysicsManager* PhysicsManager::instance;

PhysicsManager* PhysicsManager::GetInstance() {
	if (instance == NULL)
		instance = new PhysicsManager();
	return instance;
}

void PhysicsManager::OnStart() {
	//load gameobjects in scene into vector list
	_sceneObjects = SceneManager::GetInstance()->GetCurrentScene()->sceneObjects;
}

void PhysicsManager::OnUpdate(int ticks) {

	//TODO: change to iterators by beta or release
	if (_sceneColliders.size() > 1) {
		for (int i = 0; i < _sceneColliders.size() - 1; i++) {
			for (int j = i + 1; j < _sceneColliders.size(); j++) {
				if (checkCollision(_sceneColliders[i]->GetGameObject()->GetComponent<Transform*>(),
					_sceneColliders[j]->GetGameObject()->GetComponent<Transform*>()) < (_sceneColliders[i]->getRadius() + _sceneColliders[j]->getRadius())) {
					_sceneColliders[i]->setCollision(true);
					_sceneColliders[i]->setColliderObj(_sceneColliders[j]->GetGameObject());
					_sceneColliders[j]->setCollision(true);
					_sceneColliders[j]->setColliderObj(_sceneColliders[i]->GetGameObject());
				}
				else {
					_sceneColliders[i]->setCollision(false);
					_sceneColliders[i]->setColliderObj(NULL);
					_sceneColliders[j]->setCollision(false);
					_sceneColliders[j]->setColliderObj(NULL);
				}
			}
		}
	}
	/*
	for (std::map<int, GameObject*>::iterator i = _sceneObjects.begin(); i != _sceneObjects.end(); i++) {
		if (i->second->GetComponent<Collider*>()) {
			for (std::map<int, GameObject*>::iterator j = i; j != _sceneObjects.end(); j++) {
				if (j->second->GetComponent<Collider*>()) {
					Collider* cl1 = i->second->GetComponent<Collider*>();
					Collider* cl2 = j->second->GetComponent<Collider*>();
					if (checkCollision(i->second->GetComponent<Transform*>(), j->second->GetComponent<Transform*>()) < (cl1->getRadius() + cl2->getRadius())) {
						cl1->setCollision(true);
						cl1->setColliderObj(j->second);
						cl2->setCollision(true);
						cl2->setColliderObj(i->second);
					}
					else {
						cl1->setCollision(false);
						cl1->setColliderObj(NULL);
						cl2->setCollision(false);
						cl2->setColliderObj(NULL);
					}
				}
			}
		}
	//	std::prev(i);
	}
	*/
}

void PhysicsManager::addCollider(Collider* c) {
	_sceneColliders.push_back(c);
}

void PhysicsManager::removeCollider(Collider* c) {
	_sceneColliders.erase(std::remove(_sceneColliders.begin(), _sceneColliders.end(), c), _sceneColliders.end());
}

void PhysicsManager::OnEnd() {

}

float PhysicsManager::checkCollision(Transform* obj1, Transform* obj2) {
	return sqrt(pow(obj1->getX() - obj2->getX(), 2) + pow(obj1->getY() - obj2->getY(),2));
}