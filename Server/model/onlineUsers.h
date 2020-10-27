#pragma once
#include <iostream>
#include <pthread.h>
#include "server.h"
#include "user.h"
#include<vector>

#define MAX_USERS 100

static int client_count = 0;

void addUser(User *user);
void removeUser(int user_id); 
void sendMessage(char* message, int user_id);
void sendMessageToParticularUser(char* s, const char* name);
vector<string> getOnlineUsers(string name);