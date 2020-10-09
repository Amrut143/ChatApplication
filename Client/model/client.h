#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <thread>
#include<iostream>

#define PORT 8080

using namespace std;

class Client
{

    char msg[1024]; 
    char buffer[1024] = {0};

    public:    
        int connectToServer();
        void sendMessage(int);
        void recieveMessage(int);
};