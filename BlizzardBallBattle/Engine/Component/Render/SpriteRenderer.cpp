#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(GameObject* gameObject) : Component(gameObject) {
  //SpriteRendererManager::GetInstance().subscribe(gameObject.id, this);
}

void SpriteRenderer::Render() {
    //Transform* transform = gameObject.getComponent<Transform>();
    //if (transform == null)
    //    SpriteRendererManager::GetInstance().unsubscribe(gameObject.id);
    //render code
}