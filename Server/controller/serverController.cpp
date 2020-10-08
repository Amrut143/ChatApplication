#include "serverController.h"

void ServerController::acceptClientSocket()
{
    sock_fd = server.getConnectedClientSocket();

    if (sock_fd < 0)
        exit(EXIT_FAILURE);
    serverView.displayMsgToConnectedClients();
}

int main() 
{
    ServerController controller;

    controller.acceptClientSocket();
}