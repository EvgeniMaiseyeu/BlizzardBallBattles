
#include "Component.h"
#include <string>
#include <typeinfo>
#include <vector>

class GameObject {
private:
    typedef pair<string, std::vector<Component*>> components;

public:

    GameObject();

    Component* GetComponent(string *type);
    Component* GetComponents(string *type);
    void AddComponent(Component *component);
    void RemoveComponent(string *type);

    bool HasComponent(string *type);

    //template <class T>
    //vector<Component*> GetComponentsByType();
}