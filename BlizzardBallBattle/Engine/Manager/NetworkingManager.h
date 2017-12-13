#pragma once
#include "GLHeaders.h"
#include <iostream>
#include "ThreadQueue.h"
#include <thread>
#include <map>
#include <string>
#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_PORT 9999


struct Message {
    std::string key;
    std::map<std::string, std::string> data;
};

class NetworkingManager {
private:
    static NetworkingManager* instance;
    ThreadQueue<std::string> *messageQueue;
    std::thread receiverThread;
    std::vector<Message> messagesToSend;
    char *IP = DEFAULT_IP;
    int port = DEFAULT_PORT;

    TCPsocket socket = NULL;
    TCPsocket client = NULL;
    bool Accept();
    bool Host();
    bool Join();
    void PollMessages();
    void PollMessagesThread();
    std::string SerializeMessage(Message message);
    std::map<std::string, void*> DeserializeMessage(std::string message);
    void SendEventToReceiver(std::map<std::string, void*> data);

public:
	bool Close ();
    NetworkingManager();
    static NetworkingManager* GetInstance();
    bool CreateHost();
    bool CreateClient();
    void Send(std::string *msg);
    bool GetMessage(std::string &msg);
    void PrepareMessageForSending(std::string key, std::map<std::string, std::string> data);
    void SendQueuedEvents();
    void HandleParsingEvents(std::string packet);
    bool IsConnected();
    bool IsHost();
    void SetIP(char *ip, int port = DEFAULT_PORT);
};