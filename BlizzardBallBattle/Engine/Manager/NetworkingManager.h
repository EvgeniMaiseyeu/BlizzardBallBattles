#pragma once
#include "GLHeaders.h"
#include <iostream>
#include "ThreadQueue.h"
#include <thread>

class NetworkingManager {
private:
    static NetworkingManager* instance;
    ThreadQueue<std::string*> *messageQueue;
    std::thread receiverThread;

    TCPsocket socket = NULL;
    TCPsocket client = NULL;
    bool Accept();
    bool Host();
    bool Join();
    bool Close();
    bool Receive(std::string *message);
    void PollMessages();
    void PollMessagesThread();

public:
    NetworkingManager();
    static NetworkingManager* GetInstance();
    bool CreateHost();
    bool CreateClient();
    void Send(std::string *msg);
    bool GetMessage(std::string *message);
};