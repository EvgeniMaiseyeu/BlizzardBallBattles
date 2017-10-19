#pragma once

#include "GameScene.h"
#include "Battler.h"

class GameScene_Alpha_Networked : public GameScene {
private:
	Battler *player1, *player2;
	bool isConnected;
	void OnConnected();

public:
	void OnStart();
	void OnResume(){};
	void OnUpdate(int ticks);
	void OnPause(){};
	void OnEnd();
};