#pragma once

#include "Scene.h"
#include "GameObject.h"
#include "Shader.h"

class MessagingTestScene : public Scene {
private:

public:
	virtual void OnStart();
	virtual void OnUpdate();
	virtual void OnEnd();
};