#include "GameObject.h"

GameObject::GameObject() {   
}

Component* GameObject::GetComponent(std::string type) {
    return components[type].front();
}

std::vector<Component*> GameObject::GetComponents(std::string type) {
    return components[type];
}

void GameObject::AddComponent(Component *component) {
    std::string type = typeid(component).name();
    if (!HasComponent(type)) {
        std::vector<Component*> typeList;
        typeList.push_back(component);
        components[type] = typeList;
    } else {
        components[type].push_back(component);
    }
}

void GameObject::RemoveComponent(std::string type) {
    components[type].clear();
}

bool GameObject::HasComponent(std::string type) {
    return components.count(type);
}