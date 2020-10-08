#include "serverController.h"

void ServerController::acceptClientSocket()
{
    sock_fd = server.establishListener();

    if (sock_fd < 0)
        exit(EXIT_FAILURE);
    serverView.displayServerListenMsg();
    newSock_fd = server.acceptNewConnection();
    serverView.displayConnectionAcceptMsg();
}

int main() 
{
    ServerController controller;

    controller.acceptClientSocket();
}