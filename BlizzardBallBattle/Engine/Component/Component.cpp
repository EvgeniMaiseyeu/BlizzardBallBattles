#include "Component.h"

Component::Component(GameObject* gameObject) {
   this->gameObject = gameObject;
}

GameObject* Component::GetGameObject() {
 return gameObject;
}

