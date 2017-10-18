#pragma once
#include "Updateable.h"

class GameObject;

class Component : public Updateable {
public:
   Component(GameObject* gameObject);
   GameObject* GetGameObject();
   void OnStart() {};
   void OnUpdate(int ticks) {};
   void OnEnd() {};
protected:
   GameObject* gameObject;
};