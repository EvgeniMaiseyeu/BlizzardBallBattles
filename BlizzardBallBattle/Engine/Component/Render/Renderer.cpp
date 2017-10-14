#include "Renderer.h"

Renderer::Renderer(GameObject* gameObject) : Component(gameObject) {
    layer = 0;
}

int Renderer::SetLayer(int newLayer) {
    layer = newLayer;
}
int Renderer::GetLayer() {
    return layer;
}