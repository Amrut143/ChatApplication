#pragma once
#include <netinet/in.h>
#include <iostream>

using namespace std;

struct User {
    
    struct sockaddr_in address;
    int sock_fd;
    int user_id;
    string user_name = "amrut";
    string password = "1234";
};
