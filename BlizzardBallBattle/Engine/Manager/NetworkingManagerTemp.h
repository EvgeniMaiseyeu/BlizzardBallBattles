#pragma once

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <ctype.h>
#include "MessageManager.h"

struct Message {
    std::string key;
    std::map<std::string, std::string> data;
};

class NetworkingManagerTemp {
private:
    std::vector<Message> messagesToSend;

public:
    static NetworkingManagerTemp *instance;
    static NetworkingManagerTemp* GetInstance();
    void PrepareMessageForSending(std::string key, std::map<std::string, std::string> data);
    void SendQueuedEvents();
    std::string SerializeMessage(Message message);
    std::map<std::string, void*> DeserializeMessage(std::string message);
    void HandleParsingEvents(std::string packet);
    void SendEventToReceiver(std::map<std::string, void*> data);
};