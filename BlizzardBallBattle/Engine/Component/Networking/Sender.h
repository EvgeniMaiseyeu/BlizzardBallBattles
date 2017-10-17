#pragma once

#include <string>
#include "GameObject.h"
#include "NetworkingManagerTemp.h"
#include "Transform.h"
#include <iostream>

//Senders transform message and extra commands

class Sender : public Component {
private:
    std::string ID;

public:
    Sender(GameObject* gameObject, std::string ID);
    void SendUpdate();
    void SendMessage(std::string messageKey,  std::map<std::string, std::string> payload);
};