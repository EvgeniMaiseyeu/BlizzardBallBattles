#include "Entity.h"
#include "Component.h"

class SpriteRenderer:Component {
public:
    //Sprite* sprite;
    //Texture* texture;

    SpriteRenderer(Entity* entity);

    void Render();
}