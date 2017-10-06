#pragma once

#include "Component.h"
#include <string>
#include <typeinfo>
#include <vector>
#include <map>

class GameObject {
private:
    std::map<std::string, std::vector<Component*>> components;

public:

    GameObject();

    Component* GetComponent(std::string type);
    std::vector<Component*> GetComponents(std::string type);
    void AddComponent(Component *component);
    void RemoveComponent(std::string type);

    bool HasComponent(std::string type);

    //template <class T>
    //vector<Component*> GetComponentsByType();
};