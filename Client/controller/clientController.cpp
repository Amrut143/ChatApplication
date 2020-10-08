#include "clientController.h"

void ClientController::requestForConnection()
{
    clientSocket = client.connectToServer();

    if (clientSocket < 0)
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