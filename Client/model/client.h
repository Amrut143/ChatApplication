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
public:    
    int connectToServer();
    void sendMessege(int);
    void receiveMessege(int);
};