#pragma once
#include <netinet/in.h>
#include <iostream>

#define MAX_USERS 100

using namespace std;

struct User {
    
    struct sockaddr_in address;
    int sock_fd;
    int user_id;
    string user_name;
};
