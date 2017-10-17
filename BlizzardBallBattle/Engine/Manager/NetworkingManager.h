#pragma once
#include "GLHeaders.h"
#include <iostream>

class NetworkingManager {
private:
    static NetworkingManager* instance;
    TCPsocket socket = NULL;
    TCPsocket client = NULL;
    bool Accept();
    bool Host();
    bool Join();
    bool Close();

public:
    NetworkingManager();
    static NetworkingManager* GetInstance();
    bool CreateHost();
    bool CreateClient();
    void Send(std::string *msg);
    void Receive();
};