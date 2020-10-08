#pragma once
#include "../model/client.h"
#include "../view/clientView.h"

class ClientController
{
    int sock = 0;
    Client client;
    ClientView clientView;
public:
    void requestForConnection();
};