#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(Entity* entity) {
    super(entity);
    SpriteRendererManager.getInstance().subscribe(entity.id, this)
}

void SpriteRenderer::Render() {
    Transform* transform = entity.getComponent<Transform>();
    if (transform == null)
        SpriteRendererManager.getInstance().unsubscribe(entity.id);
    //render code
}