#pragma once
#include "GLHeaders.h"
#include <iostream>

class NetworkingManager {
private:
    static NetworkingManager* instance;
    TCPsocket socket;
    TCPsocket client = NULL;

public:
    NetworkingManager();
    static NetworkingManager* GetInstance();
    void Host();
    void Join();
    void Send(std::string *msg);
    void Receive();
    void Accept();
};