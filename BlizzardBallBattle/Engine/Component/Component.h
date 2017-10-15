#pragma once

class GameObject;

class Component {
public:
   Component(GameObject* gameObject);
   GameObject* GetGameObject();
   void Update(int ticks);
protected:
   GameObject* gameObject;
};