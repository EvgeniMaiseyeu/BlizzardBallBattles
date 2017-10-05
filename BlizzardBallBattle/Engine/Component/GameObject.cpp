#include "GameObject.h"

GameObject::GameObject() {
    
}

Component* GameObject::GetComponent(string *type) {
    return components[type].front();
}

Component* GameObject::GetComponents(string *type) {
    return components[type];
}

void GameObject::AddComponent(Component *component) {
    string *type = typeid(component).name();
    if (components[type] == null) {
        std::vector<Component*> typeList;
        typeList.push_back(component);
        components[type] = typeList;
    } else {
        comonents[type].push_back(component);
    }
}

void GameObject::RemoveComponents(string *type) {
    components[type].clear();
}

bool GameObject::HasComponent(string *type) {
    return components[type] != null;
}