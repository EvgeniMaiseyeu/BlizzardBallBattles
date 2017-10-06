#pragma once

class GameObject;

class Component {
public:
    Component(GameObject* gameObject);
private:
    GameObject* gameObject;
};