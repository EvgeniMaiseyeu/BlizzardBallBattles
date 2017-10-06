#include "GameObject.h"
#include "Transform.h"

GameObject::GameObject() {
  AddComponent("Transform", (Component*)new Transform(this));
}

Component* GameObject::GetComponent(std::string type) {
    return components[type].front();
}

std::vector<Component*> GameObject::GetComponents(std::string type) {
    return components[type];
}

void GameObject::AddComponent(std::string componentKey, Component *component) {
    //std::string type = typeid(component).name(); NOTE: This returns "class Component *" for a SpriteRenderer type, not a valid way to get the string type of a object
    if (!HasComponent(componentKey)) {
        std::vector<Component*> typeList;
        typeList.push_back(component);
        components[componentKey] = typeList;
    } else {
        components[componentKey].push_back(component);
    }
}

void GameObject::RemoveComponent(std::string type) {
    components[type].clear();
}

bool GameObject::HasComponent(std::string type) {
    return components.count(type);
}