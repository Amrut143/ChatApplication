#include "clientController.h"


void ClientController::sendMsg(int sock)
{
    while(true)
    {
	    client.sendMessage(sock);
    }  
}

void ClientController::recieveMsg(int sock)
{
    while(true)
    {
        client.recieveMessage(sock);
    }
    
}

void ClientController::requestForConnection()
{
    client_socket = client.connectToServer();

    if (client_socket < 0)
    {
         exit(EXIT_FAILURE);
    }
    clientView.displayMessages();

	thread send_thread (&ClientController::sendMsg, this, client_socket);
	thread recv_thread (&ClientController::recieveMsg, this, client_socket);

	send_thread.join();
	recv_thread.join();

	close(client_socket);
}

int main() 
{
    ClientController controller;

    controller.requestForConnection();

}