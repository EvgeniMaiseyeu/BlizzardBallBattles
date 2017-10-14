#include "Renderer.h"

Renderer::Renderer(GameObject* gameObject) : Component(gameObject) {
    layer = RENDER_LAYER_DEFAULT;
}

int Renderer::SetLayer(int newLayer) {
    layer = newLayer;
}
int Renderer::GetLayer() {
    return layer;
}