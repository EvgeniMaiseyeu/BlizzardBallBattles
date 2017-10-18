#pragma once

#include "GameObject.h"

class Scene : public Updateable {
private: 
    std::map<int, GameObject*> sceneObjects;

public:
    //Called on unpausing from the SceneManager's scene stack.
    virtual void OnResume() = 0;

    //Called when pausing the scene when another scene is added on top of SceneManager's stack.
    virtual void OnPause() = 0;

    //Add a game object that belongs to this scene. Global objects will not be here, but in Game Manager.
    void AddGameObject(int id, GameObject* obj);
     
    //Remove a game object from the scene
    void RemoveGameObject(int id);
};