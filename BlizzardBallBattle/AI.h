#pragma once

#ifndef AI_H
#define AI_H

#include "Component.h"
#include <exception>
#include "Battler.h"
#include <vector>
#include <iostream>

class AI :
	public Component
{
private:
	Battler* myBattler;
	GameObject* target;
public:
	AI(GameObject* gameObject);
	~AI();
	void Init();
	GameObject* GetTarget();
};

#endif