#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <iostream>

#define LENGTH 2048

using namespace std;

void sendDataToServer(string, int);
string readResponseFromServer(int);