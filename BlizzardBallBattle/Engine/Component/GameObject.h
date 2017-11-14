#pragma once

#include "Component.h"
#include <string>
#include <typeinfo>
#include <vector>
#include <map>
#include "Updateable.h"

class GameObject : public Updateable {
private:
   std::map<std::string, std::vector<Component*>> components;
   //std::map<std::string, Mix_Music> mMusic;
   //std::map<std::string, Mix_Chunk> mSEF;

   int id;
   bool isGlobal;
   
   template <typename T>
   std::string GetClassName() {
       return typeid(T).name();
   }

public:
   //static GameObject* Instance();
  // Mix_Music* GetMusic(std::string filename);
  // Mix_Chunk* GetSEF(std::string filename);
   GameObject(bool isGlobal);

   int getId() {
       return id;
   }

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

   void OnStart() {};
   void OnUpdate(int ticks);
   void OnEnd() {};
   
   ~GameObject();

   //template <class T>
   //vector<Component*> GetComponentsByType();
};