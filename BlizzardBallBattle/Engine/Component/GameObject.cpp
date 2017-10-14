#include "GameObject.h"
#include "Transform.h"

GameObject::GameObject() {
  id = rand() + rand();
  GameManager::GetInstance()->AddGameObject(id, this);
  AddComponent<Transform*>(new Transform(this));
}

void GameObject::Update(int ticks) {
    for (std::map<std::string, std::vector<Component*>>::iterator it=components.begin(); it!=components.end(); ++it) {
        for (size_t i = 0; i < it->second.size(); i++){
            it->second[i]->Update(ticks);
        }
    }
}

GameObject::~GameObject() {
  GameManager::GetInstance()->RemoveGameObject(id);
}