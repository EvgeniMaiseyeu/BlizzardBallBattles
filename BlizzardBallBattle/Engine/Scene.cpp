#include "Scene.h"
#include "SpriteRenderer.h"
#include "Collision/Collider.h"
#include "SpriteRendererManager.h"
#include "PhysicsManager.h"

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


void Scene::Purge() {
	for (std::map<int, GameObject*>::iterator it = sceneObjects.begin(); it != sceneObjects.end(); ++it) {
		SpriteRenderer* renderer = it->second->GetComponent<SpriteRenderer*>();
		Collider* collider = it->second->GetComponent<Collider*>();
		if (renderer != NULL) {
			SpriteRendererManager::GetInstance()->RemoveSpriteFromRendering(renderer);
		}
		if (collider != NULL) {
			PhysicsManager::GetInstance()->removeCollider(collider);
		}
	}
}