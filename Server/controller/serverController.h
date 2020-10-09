#pragma once
#include <thread>
#include "../model/server.h"
#include "../view/serverView.h"

class ServerController
{
    int sock_fd;
    int newSock_fd;
    Server server;
    ServerView serverView;

    public:
        void acceptClientSocket();
        void sendMsg(int);
        void recieveMsg(int);
};