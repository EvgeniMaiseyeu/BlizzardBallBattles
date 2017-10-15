#pragma once

#include "Component.h"

class Renderer : public Component {
protected:
    int layer;

public:
    Renderer(GameObject* gameObject);
    int SetLayer(int newLayer);
    int GetLayer();
};