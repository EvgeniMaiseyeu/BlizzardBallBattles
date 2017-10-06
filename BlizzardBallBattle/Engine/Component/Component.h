#pragma once

class GameObject;

class Component {
public:
    Component(GameObject* gameObject);
    GameObject* GetGameObject();
protected:
    GameObject* gameObject;
};