#pragma once

#include "Scene.h"
#include "SimpleSprite.h"
#include "Shader.h"

class MenuScene_Alpha : public Scene {
private:
    SimpleSprite* menuBackground;
    SimpleSprite* menuForeground;
protected:
    Shader* pixelShader;

public:
    virtual void OnEnd();

    void BuildBaseScene();
};