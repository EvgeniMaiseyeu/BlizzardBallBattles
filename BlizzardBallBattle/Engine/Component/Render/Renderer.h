#pragma once

#include "Component.h"

#define RENDER_LAYER_DEFAULT 0

class Renderer : public Component {
protected:
    int layer;

public:
    Renderer(GameObject* gameObject);
    int SetLayer(int newLayer);
    int GetLayer();
};