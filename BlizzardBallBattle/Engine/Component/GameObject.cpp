#include "GameObject.h"
#include "Transform.h"
#include "GameManager.h"
#include "SceneManager.h"
 
GameObject::GameObject(bool g) {
    id = rand() + rand();
    isGlobal = g;
    if (isGlobal)
        GameManager::GetInstance()->AddGameObject(id, this);
    Scene *scene = SceneManager::GetInstance()->GetCurrentScene();
    if (scene != NULL)
        scene->AddGameObject(id, this);
    AddComponent<Transform*>(new Transform(this));
}
 
void GameObject::OnStart() {}

void GameObject::OnUpdate(int ticks) {
    for (std::map<std::string, std::vector<Component*>>::iterator it=components.begin(); it!=components.end(); ++it) {
        for (size_t i = 0; i < it->second.size(); i++){
            it->second[i]->OnUpdate(ticks);
        }
    }
}

void GameObject::OnEnd() {}
 
GameObject::~GameObject() {
  GameManager::GetInstance()->RemoveGameObject(id);
}