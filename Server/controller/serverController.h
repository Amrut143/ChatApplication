#pragma once
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
};