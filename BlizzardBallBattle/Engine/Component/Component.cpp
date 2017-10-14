#include "Component.h"

Component::Component(GameObject* gameObject) {
    this->gameObject = gameObject;
}

void Component::Update(int ticks) {

}

GameObject* Component::GetGameObject() {
  return gameObject;
}