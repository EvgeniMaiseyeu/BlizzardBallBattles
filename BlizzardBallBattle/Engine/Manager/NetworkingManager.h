#pragma once
#include "GLHeaders.h"
#include <iostream>

class NetworkingManager {
private:
    static NetworkingManager* instance;
    TCPsocket socket;
    TCPsocket client;

public:
    NetworkingManager();
    static NetworkingManager* GetInstance();
    void Host();
    void Join();
    void Send();
    void Receive();
    void Accept();
};