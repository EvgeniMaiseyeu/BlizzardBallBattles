#pragma once

#include "Component.h"
#include "Transform.h"
#include "Vector2.h"
#include <string>
#include <typeinfo>
#include <vector>
#include <map>

class GameObject {
private:
    std::map<std::string, std::vector<Component*>> components;
    
    template <typename T>
    std::string GetClassName() {
        return typeid(T).name();
    }

public:

    GameObject();

    template <typename T> 
    T GetComponent() {
        return (T)components[GetClassName<T>()].front();
    }
    
    template <typename T> 
    std::vector<T> GetComponents() {
        return (T)components[GetClassName<T>()];
    }
    
    template <typename T> 
    void AddComponent(T component) {
        std::string id = GetClassName<T>();
        if (!HasComponent<T>()) {
            std::vector<Component*> typeList;
            typeList.push_back((Component*)component);
            components.insert(std::pair<std::string, std::vector<Component*>>(id, typeList));
        } else {
            components[id].push_back(component);
        }
    }
    
    template <typename T> 
    void RemoveComponent() {
        components[GetClassName<T>()].clear();
    }
    
    template <typename T> 
    bool HasComponent() {
        return components.count(GetClassName<T>()) > 0;
    }
    

    //template <class T>
    //vector<Component*> GetComponentsByType();
};