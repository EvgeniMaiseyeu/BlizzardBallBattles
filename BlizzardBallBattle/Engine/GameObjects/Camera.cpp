#include "Camera.h"
#include "DayNightCamera.h"

Camera* Camera::activeCamera = new DayNightCamera();

Camera::Camera() : GameObject(true) {
    init = false;
}

void Camera::ApplyRenderFilters(SpriteRendererManager* rendererManager) {
    rendererManager->RenderPass();
}

void Camera::SetActiveCamera(Camera* camera) {
    activeCamera->NotifyInactivity();
    activeCamera = camera;
}

Camera* Camera::GetActiveCamera() {
    return activeCamera;
}

void Camera::NotifyInactivity() {
    delete(this);
}


void Camera::EnsureInit() {
    if (!init) {
        Init();
        init = true;
    }
}

void Camera::Init() {}