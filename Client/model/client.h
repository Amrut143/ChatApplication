#pragma once
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include<iostream>
#include <thread>

#define PORT 8080

using namespace std;

class Client
{
    int connectToServer();
};