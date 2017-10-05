#include "SpriteRendererManager.h"

static SpriteRendererManager* SpriteRendererManager::getInstance() {
    if (SpriteRendererManager.instance == null)
        SpriteRendererManager.instance = new SpriteRendererManager();
    return SpriteRendererManager.instance;
}

void SpriteRendererManager::Subscribe(int id, SpriteRender* spriteRenderer) {
    spriteRenderers[id] = spriteRenderer;
}

void SpriteRendererManager::UnSubscribe(int id) {
    spriteRenderers.erase(id);
}

void SpriteRendererManager::Update(int ticks) {
    for (std::map<int,SpriteRenderer*>::iterator renderer=spriteRenderers.begin(); renderer!=spriteRenderers.end(); ++renderer)
        spriteRenderer.Render();
}