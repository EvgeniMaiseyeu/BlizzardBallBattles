#pragma once

#include "Scene.h"
#include "GameObject.h"
#include "Shader.h"



class GameScene_Alpha_Networked : public Scene {
private:
	Shader* ourShader;
	GameObject *player1, *player2;
	bool isConnected;
	void OnConnected();
	void GenerateBackgroundTiles();

public:
	virtual void OnStart();
	virtual void OnUpdate();
	virtual void OnEnd();
};