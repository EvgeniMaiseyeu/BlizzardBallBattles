#pragma once

#include "GameObject.h"
#include "Component.h"

class SpriteRenderer:Component {
public:
    //Sprite* sprite;
    //Texture* texture;

    SpriteRenderer(GameObject* gameObject);

    void Render();
};