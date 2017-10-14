#include "NetworkingManagerTemp.h"

NetworkingManagerTemp* NetworkingManagerTemp::instance;

NetworkingManagerTemp* NetworkingManagerTemp::GetInstance() {
    if (instance == NULL)
        instance = new NetworkingManagerTemp();
    return instance;
}

void NetworkingManagerTemp::PrepareMessageForSending(std::string key, std::map<std::string, std::string> data) {
    Message message;
    message.key = key;
    message.data = data;
    messagesToSend.push_back(message);
}

void NetworkingManagerTemp::SendQueuedEvents() {
    std::string packet = "[";
    for(size_t i = 0; i < messagesToSend.size(); i++) {
        packet += SerializeMessage(messagesToSend[i]);
        packet += ",";
    }
    packet.pop_back();
    packet += "]";
    //std::cout << packet << std::endl;
    //Submit it
    messagesToSend.clear();

    HandleParsingEvents(packet);
}

void NetworkingManagerTemp::SendEventToReceiver(std::map<std::string, void*> data) {
    std::string key = (std::string*)data["key"];
    std::cout << "Sending Event " << key << " x:" << (char*)data["x"] << std::endl;
    MessageManager::SendEvent(key, data );
}

std::string NetworkingManagerTemp::SerializeMessage(Message message) {
    std::string result = "{";
    message.data["key"] = message.key.c_str();

    for (const auto tuple : message.data) {
        result += tuple.first + " : " + message.data[tuple.first] + ",";
    }
    result.pop_back();
    result += "}";
    return result;
}


void NetworkingManagerTemp::HandleParsingEvents(std::string packet) {
    std::vector<std::string> messages;
    packet.erase(0, 1);
    packet.pop_back();
    std::string currentMessage = "";
    bool reading = false;
    while(packet.size() > 0) {
        if (!reading) {
            if (packet[0] == '{') {
                reading = true;
                currentMessage += packet[0];
            }
        } else {
            currentMessage += packet[0];
            if (packet[0] == '}') {
                reading = false;
                messages.push_back(currentMessage);
                //std::cout << "PUSHBACK: " << currentMessage;
                SendEventToReceiver(DeserializeMessage(currentMessage));
                currentMessage = "";
            }
        }

        packet.erase(0, 1);
    }
}



//TODO: Deserialize this:
//Example: {key : Player|UPDATE,rotation : 37.000000,scale : 1.000000,x : 1.000000,y : 0.000000}

std::map<std::string, void*> NetworkingManagerTemp::DeserializeMessage(std::string message) {
    std::map<std::string, void*> data;
    std::string currentKey = "";
    std::string currentValue = "";
    bool readingKey;
    bool readingValue;
    while(message.size() > 0) {
        char curChar = message[0];
        message.erase(0, 1);
        
        if (curChar == ',' || curChar == '{') {
            //Start reading key
            readingKey = true;
            readingValue = false;
            if (curChar == ',') {
                data[currentKey] = (void*)new std::string(currentValue);
                std::cout << currentKey << " " << (char*)data[currentKey] << std::endl;
            }
            std::string newCurrentString = "";
            std::string newCurrentValue = "";
            currentKey = newCurrentString;
            currentValue = newCurrentValue;
            continue;
        } else if (curChar == ':') {
            //Start reading value
            readingValue = true;
            readingKey = false;
            continue;
        } else if (curChar == '}') {
            //End
            data[currentKey] = (void*)new std::string(currentValue);
            std::cout << currentKey << " " << (char*)data[currentKey] << std::endl;
            break;
        }
        if (!isspace(curChar)) {
            if (readingKey) {
                currentKey += curChar;
            } else if (readingValue) {
                currentValue += curChar;
            }
        }

    }
    return data;
}