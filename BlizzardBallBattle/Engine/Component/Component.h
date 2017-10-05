#include "Entity.h"

class Component {
public:
    Component(Entity* entity);
private:
    Entity* entity;
}