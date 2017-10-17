#include "NetworkingManager.h"

NetworkingManager* NetworkingManager::instance;

NetworkingManager* NetworkingManager::GetInstance() {
    if (instance == NULL)
        instance = new NetworkingManager();
    return instance;
}

NetworkingManager::NetworkingManager() {
    SDLNet_Init();
    messageQueue = new ThreadQueue<std::string*>();
}

bool NetworkingManager::CreateHost() {
    return Host();
}

bool NetworkingManager::CreateClient() {
    return Join();
}

bool NetworkingManager::Host() {
    // create a listening TCP socket on port 9999 (server)
    IPaddress ip;

    int startConnTime = SDL_GetTicks();
    int timeoutTime = SDL_GetTicks();
    const int TIMEOUT = 60000;

    ip.host = 2130706433;
    ip.port = 5050;

    if(SDLNet_ResolveHost(&ip,NULL,9999)==-1) {
        printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
        return false;
    }

    socket=SDLNet_TCP_Open(&ip);
    if(!socket) {
        printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
        return false;
    }
    bool result = false;
    while(!(result = Accept()) && SDL_GetTicks() - startConnTime < TIMEOUT);
    if  (result) {
        std::cout << "Connection established." << std::endl;
        PollMessages();
        return true;
    } else {
        std::cout << "No peer found, destroying server." << std::endl;
        Close();
        return false;
    }
}

bool NetworkingManager::Join() {
    IPaddress ip;

    ip.host = 3232235623;
    ip.port = 5050;
    
    if(SDLNet_ResolveHost(&ip,"192.168.0.103",9999)==-1) {
        printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
        return false;
    }
    
    socket=SDLNet_TCP_Open(&ip);
    if(!socket) {
        printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
        Close();
        return false;
    }
    std::cout << "SDLNet_TCP_Open:A>A>A WE DID IT JOIN" << std::endl;
    PollMessages();
    return true;
}

bool NetworkingManager::Accept() {
    client=SDLNet_TCP_Accept(socket);
    if(!client) {
        printf("SDLNet_TCP_Accept: %s\n", SDLNet_GetError());
        return false;
    }
    // communicate over new_tcpsock
    std::cout << "SDLNet_TCP_Accept:A>A>A WE DID IT ACCETP" << std::endl;
    return true;
}

bool NetworkingManager::Close() {
    if (client != NULL)
        SDLNet_TCP_Close(client);
    if (socket != NULL)
        SDLNet_TCP_Close(socket);
    return true;
}

void NetworkingManager::Send(std::string *msg) {
    // send a hello over sock
    //TCPsocket sock;
    int result,len;
    len = msg->length() + 1;

    if (client != NULL)
        result=SDLNet_TCP_Send(client, msg->c_str(), len);
    else
        result=SDLNet_TCP_Send(socket, msg->c_str(), len);
    if(result<len) {
        printf("SDLNet_TCP_Send: %s\n", SDLNet_GetError());
    }
}

bool NetworkingManager::Receive(std::string *message) {
    // receive some text from sock
    //TCPsocket sock;
    #define MAXLEN 1024
    int result;
    char msg[MAXLEN];

    if (client != NULL)
        result=SDLNet_TCP_Recv(client, msg, MAXLEN);
    else if (socket != NULL)
        result=SDLNet_TCP_Recv(socket, msg, MAXLEN);
    if(result<=0) {
        // An error may have occured, but sometimes you can just ignore it
        // It may be good to disconnect sock because it is likely invalid now.
        return false;
    }
    message = new std::string(msg);
    return true;
}

void NetworkingManager::PollMessages() {
    receiverThread = std::thread(&NetworkingManager::PollMessagesThread, this);
    receiverThread.join();
}

void NetworkingManager::PollMessagesThread() {
    #define MAXLEN 1024
    int result;
    char msg[MAXLEN];

    while(1) { //replace with on connection lost

    if (client != NULL)
        result=SDLNet_TCP_Recv(client, msg, MAXLEN);
    else if (socket != NULL)
        result=SDLNet_TCP_Recv(socket, msg, MAXLEN);
    if(result<=0) {
        // An error may have occured, but sometimes you can just ignore it
        // It may be good to disconnect sock because it is likely invalid now.
        continue;
    }
    messageQueue->Push(new std::string(msg));
    }
}

bool NetworkingManager::GetMessage(std::string *message) {
    if (!messageQueue->IsEmpty()) {
        messageQueue->Pop(message);
        return true;
    }
    return false;
}