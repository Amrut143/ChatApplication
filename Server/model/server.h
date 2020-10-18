#pragma once
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <signal.h>
#include <iostream>
#include <string>
#include <pthread.h>
#include "user.h"
#include <list>
#include <thread>

#define ALREADY_EXIST "1"
#define PORT 7777

static int user_id = 10;

class Server
{
    User *users[MAX_USERS];
    pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

    public:
        int getClientSocket();
        User* acceptNewConnection(int);
        void addUser(User *user);
        void removeUser(int user_id); 
        void sendMessage(char* message, int user_id);
        void sendMessageToParticularUser(char* s, const char* name);
};