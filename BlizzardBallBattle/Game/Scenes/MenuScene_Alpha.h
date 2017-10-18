#pragma once

#include "Scene.h"
#include "GameObject.h"
#include "Shader.h"

class MenuScene_Alpha : public Scene {
    GameObject* menuBackground;
    GameObject* menuForeground;
    GameObject* menuTitle;
    Shader* ourShader;
public:
    virtual void OnStart();
    virtual void OnUpdate();
    virtual void OnEnd();
};