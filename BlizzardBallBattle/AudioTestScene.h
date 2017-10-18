#pragma once

#include "Scene.h"
#include "Shader.h"
#include "AudioManager.h"
#include <string>


class AudioTestScene : public Scene {
private:
	Shader* ourShader;
	//AudioManager* Audiomgr;

public:
	virtual void OnStart();
	virtual void OnUpdate();
	virtual void OnEnd();
};
