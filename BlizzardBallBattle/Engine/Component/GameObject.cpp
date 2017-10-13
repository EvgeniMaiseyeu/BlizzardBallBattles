#include "GameObject.h"

GameObject::GameObject() {
  AddComponent<Transform*>(new Transform(this));
}

