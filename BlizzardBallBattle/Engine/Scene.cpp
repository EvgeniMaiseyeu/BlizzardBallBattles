#include "Scene.h"

void Scene::AddGameObject(int id, GameObject* obj) {
    sceneObjects[id] = obj;
}
 
void Scene::RemoveGameObject(int id) {
    sceneObjects.erase(id);
}