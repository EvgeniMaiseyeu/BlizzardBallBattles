#pragma once

#include <string>
#include "GameManager.h"
#include "TransformState.h"
#include "GameObject.h"
#include <vector>
#include "MessageManager.h"
#include "Transform.h"
#include <iostream>

class Receiver : public Component {
private:
	int OnUpdateID, DestroySnowballID, DestroyBattlerID;
    std::vector<int> messengingIDs;

public:
    int Subscribe(std::string event, Callback callback, void* owner);
    Receiver(GameObject* gameObject, std::string netID);
    ~Receiver(); //Could be death message later
    //void ReceiveUpdate(TransformState* equivalentTransform);
	void OnStart(){};
	void OnUpdate(int ticks){};
	void OnEnd(){};
	std::string netID;
};