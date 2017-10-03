
#include "Component.h"
#include <vector>

class GameObject {
public:
    GameObject();
    Component* GetComponent(int id);
    int AddComponent();
    void RemoveComponent(int id);

    bool HasComponent();

    template <class T>
    vector<Component*> GetComponentsByType();
}