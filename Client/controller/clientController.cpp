#include "clientController.h"

void ClientController::requestForConnection()
{
    client_socket = client.connectToServer();

    if (client_socket < 0)
    {
         exit(EXIT_FAILURE);
    }
    clientView.displayMesseges();
}

int main() 
{
    ClientController controller;

    controller.requestForConnection();
}