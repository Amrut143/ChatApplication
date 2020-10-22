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

#define PORT 7777

static int user_id = 10;

class Server {
    
    public:
        int getClientSocket();
        User* acceptNewConnection(int);
};