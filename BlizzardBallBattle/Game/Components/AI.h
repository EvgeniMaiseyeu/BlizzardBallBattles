#pragma once

#ifndef AI_H
#define AI_H

#include "Component.h"
#include <exception>
#include "GameObject.h"
#include "Battler.h"
#include <vector>
#include <iostream>

class AI :
	public Component
{
private:
	Battler* myBattler;
	GameObject* target;
	void EngageTarget();
public:
	AI(GameObject* gameObject);
	~AI();
	void Init();
	GameObject* GetTarget();
	void OnStart(){};
	void OnUpdate(int ticks){};
	void OnEnd(){};
};

#endif