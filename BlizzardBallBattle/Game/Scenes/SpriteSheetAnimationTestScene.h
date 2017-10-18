#pragma once

#include "Scene.h"
#include "GameObject.h"
#include "Shader.h"



class SpriteSheetAnimationTestScene : public Scene {
private:
	Shader* ourShader;
	GameObject *player1, *player2;

public:
	virtual void OnStart();
	virtual void OnUpdate();
	virtual void OnEnd();
};