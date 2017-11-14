#pragma once

#include "Scene.h"
#include "Shader.h"


class AudioTestScene : public Scene {
private:
	Shader* ourShader;
	//AudioManager* Audiomgr;

public:
	void OnStart();
	void OnResume() {};
	void OnUpdate(int ticks);
	void OnPause() {};
	void OnEnd();
};
