#pragma once

#ifndef MATCH_MANAGER_H
#define MATCH_MANAGER_H
#include <iostream>
#include "GameObject.h"
#include "Battler.h"
#include "AI.h"
#include <vector>

class MatchManager
{
private:
	//Singleton variables
	static MatchManager *instance;
	std::vector<Battler*> teamOne;
	std::vector<Battler*> teamTwo;
	Battler* playerOne;
	Battler* playerTwo;
	std::vector<AI*> aiUnits;
	int TEAM_SIZE;
public:
	static MatchManager* GetInstance();
	MatchManager();
	~MatchManager();
	void StartGame();
	bool RegisterCharacter(Battler *character);
	bool UnRegisterCharacter(Battler *character);
	void CreateBattlers(Shader *shader, GLuint characterTexture, GLuint spriteSheetTexture);
	std::vector<Battler*> GetTeam(int teamID);
	void Stop();
};
#endif