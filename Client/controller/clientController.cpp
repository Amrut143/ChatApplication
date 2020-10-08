#include "clientController.h"

void ClientController::requestForConnection()
{
    sock = client.connectToServer();

    if (sock < 0)
        exit(EXIT_FAILURE);
    clientView.displayMesseges();
}

int main() 
{
    ClientController controller;

    controller.requestForConnection();
}