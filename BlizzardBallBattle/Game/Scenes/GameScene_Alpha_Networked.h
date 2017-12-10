#pragma once

#include "GameScene.h"
#include "Battler.h"

class GameScene_Alpha_Networked : public GameScene {
private:
	bool isConnected;
	void OnConnected();
	int p1ai;
	int p2ai;

public:
	GameScene_Alpha_Networked(int p1ai, int p2ai);
	void OnStart();
	void OnResume(){};
	void OnUpdate(int ticks);
	void OnPause();
	void OnEnd();
};