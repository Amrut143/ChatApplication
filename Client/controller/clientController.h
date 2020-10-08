#include "../model/client.h"
#include "../view/clientView.h"

class ClientController
{
public:
    int clientSocket = 0;
    Client client;
    ClientView clientView;
    void requestForConnection();
};