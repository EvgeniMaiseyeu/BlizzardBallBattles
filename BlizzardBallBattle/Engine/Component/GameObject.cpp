#include "GameObject.h"
#include "Transform.h"

GameObject::GameObject() {
  AddComponent<Transform*>(new Transform(this));
}

