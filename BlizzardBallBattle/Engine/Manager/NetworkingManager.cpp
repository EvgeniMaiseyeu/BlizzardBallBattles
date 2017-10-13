#include "NetworkingManager.h"

NetworkingManager* NetworkingManager::instance;

NetworkingManager* NetworkingManager::GetInstance() {
    if (instance == NULL)
        instance = new NetworkingManager();
    return instance;
}

NetworkingManager::NetworkingManager() {
    SDLNet_Init();
}

void NetworkingManager::Host() {
    // create a listening TCP socket on port 9999 (server)
    IPaddress ip;

    ip.host = 2130706433;
    ip.port = 5050;

    if(SDLNet_ResolveHost(&ip,NULL,9999)==-1) {
        printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
        exit(1);
    }

    socket=SDLNet_TCP_Open(&ip);
    if(!socket) {
        printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
        exit(2);
    }
    std::cout << "SDLNet_TCP_OpenS??S?S: WE DID IT HOST" << std::endl;
}

void NetworkingManager::Join() {
    IPaddress ip;

    ip.host = 2130706433;
    ip.port = 5050;
    
    if(SDLNet_ResolveHost(&ip,"localhost",9999)==-1) {
        printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
        exit(1);
    }
    
    socket=SDLNet_TCP_Open(&ip);
    if(!socket) {
        printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
        exit(2);
    }
    std::cout << "SDLNet_TCP_Open:A>A>A WE DID IT JOIN" << std::endl;
}

void NetworkingManager::Accept() {
    client=SDLNet_TCP_Accept(socket);
    if(!client) {
        printf("SDLNet_TCP_Accept: %s\n", SDLNet_GetError());
        return;
    }
    // communicate over new_tcpsock
    std::cout << "SDLNet_TCP_Accept:A>A>A WE DID IT ACCETP" << std::endl;
}

void NetworkingManager::Send() {
    // send a hello over sock
    //TCPsocket sock;
    int result,len;
    std::string *test = new std::string("HELLO");

    len = test->length();

    if (client != NULL)
        result=SDLNet_TCP_Send(client, test, len);
    else
        result=SDLNet_TCP_Send(socket, test, len);
    if(result<len) {
        printf("SDLNet_TCP_Send: %s\n", SDLNet_GetError());
    }
}

void NetworkingManager::Receive() {
    // receive some text from sock
//TCPsocket sock;
#define MAXLEN 1024
int result;
char msg[MAXLEN];

result=SDLNet_TCP_Recv(socket, msg, MAXLEN);
if(result<=0) {
    // An error may have occured, but sometimes you can just ignore it
    // It may be good to disconnect sock because it is likely invalid now.
}
 std::cout << "MESSAGE: " << std::string(msg) << std::endl;
}