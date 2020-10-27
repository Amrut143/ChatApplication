#pragma once
#include <iostream>
#include "../utility/clientUtility.h"

#define REGISTRATION 2
#define LOGIN 1
#define VALID "0"
#define INVALID "1"

class ClientView {

    string user_id;

    public:
        string login(int);
        string registration(int);
        bool registrationAndLogin(int);
        void displayMenu();
};