#include "Scene.h"

void Scene::AddGameObject(int id, GameObject* obj) {
    sceneObjects[id] = obj;
}
 
void Scene::RemoveGameObject(int id) {
    sceneObjects.erase(id);
}

void Scene::OnObjectsUpdate(int ticks) {
    for (std::map<int, GameObject*>::iterator it=sceneObjects.begin(); it!=sceneObjects.end(); ++it) {
        it->second->OnComponentsUpdate(ticks);
        it->second->OnUpdate(ticks);
    }
}