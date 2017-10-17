#pragma once

#include "Scene.h"
#include "GameObject.h"
#include "Shader.h"

class SceneTemplate : public Scene {
private:
	Shader* ourShader;

public:
	virtual void OnStart();
	virtual void OnUpdate();
	virtual void OnEnd();
};