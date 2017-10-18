#pragma once

#include "Scene.h"
#include "GameObject.h"
#include "Shader.h"

class SceneTemplate : public Scene {
private:
	Shader* ourShader;

public:
	void OnStart();
	void OnUpdate();
	void OnEnd();
};