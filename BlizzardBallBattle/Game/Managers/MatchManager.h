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
	std::vector<AI*> aiUnits;
	const int TEAM_SIZE = 10;
public:
	static MatchManager* GetInstance();
	MatchManager();
	~MatchManager();
	void StartGame();
	bool RegisterCharacter(Battler *character);
	void CreateMap(Shader *shader, GLuint snowTexture, GLuint iceTexture);
	void CreateBattlers(Shader *shader, GLuint characterTexture, GLuint spriteSheetTexture);
	std::vector<Battler*> GetTeam(int teamID);
};
#endif