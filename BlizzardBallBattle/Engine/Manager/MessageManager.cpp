#include "MessageManager.h"

MessageManager* MessageManager::instance;

MessageManager* MessageManager::GetInstance() {
    if (instance == NULL)
        instance = new MessageManager();
    return instance;
}

int MessageManager::Subscribe(std::string event, Callback callback) {
    MessageManager* self = MessageManager::GetInstance();

    int id = rand();

    std::map<std::string, std::map<int, Callback> >::iterator it = self->subs.find(event);
    if (it != self->subs.end())
        it->second[id] = callback;
    else {
        std::map<int, Callback> eventList;
        eventList[id] = callback;
        self->subs[event] = eventList;
    }
    return id;
}

void MessageManager::UnSubscribe(std::string event, int id) {
    MessageManager* self = MessageManager::GetInstance();

    std::map<std::string, std::map<int, Callback> >::iterator it = self->subs.find(event);
    if (it != self->subs.end())
        it->second.erase(id);
}

void MessageManager::SendEvent(std::string event, std::map<std::string, void*> data) {
    MessageManager* self = MessageManager::GetInstance();

    std::map<std::string, std::map<int, Callback> >::iterator it = self->subs.find(event);
    if (it != self->subs.end())
        for (std::map<int, Callback>::iterator it2=it->second.begin(); it2!=it->second.end(); ++it2) {
            it2->second(data);
        }
}