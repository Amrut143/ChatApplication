#include "serverController.h"

void ServerController::sendMsg(int sock)
{
    while(true)
    {
        server.sendMessage(sock);
    }
}

void ServerController::recieveMsg(int sock)
{
    while(true)
    {
        server.recieveMessage(sock);
    }
}

void ServerController::acceptClientSocket()
{
    sock_fd = server.establishListener();

    if (sock_fd < 0)
        exit(EXIT_FAILURE);
    serverView.displayServerListenMsg();
    newSock_fd = server.acceptNewConnection();
    serverView.displayConnectionAcceptMsg();

    thread send_thread (&ServerController::sendMsg, this, newSock_fd);
	thread recv_thread (&ServerController::recieveMsg, this, newSock_fd);

	send_thread.join();
	recv_thread.join();

	close(sock_fd);
}

int main() 
{
    ServerController controller;

    controller.acceptClientSocket();
}