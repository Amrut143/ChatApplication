#include "../model/client.h"
#include "../view/clientView.h"

class ClientController
{
    int client_socket = 0;
    Client client;
    ClientView clientView;

    public:
        void requestForConnection();
};