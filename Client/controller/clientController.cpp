#include "clientController.h"


void ClientController::sendMessege(int sock)
{
	while(true)
    {
		client.sendMessege(sock);
	}  
}

void ClientController::receiveMessege(int sock)
{
	char buffer[1024] = {0}; 

	while(true)
    {
        client.receiveMessege(sock);
	}
    
}
void ClientController::requestForConnection()
{
    client_socket = client.connectToServer();

    if (client_socket < 0)
    {
         exit(EXIT_FAILURE);
    }

	std::thread send_thread (sendMessege, client_socket);
	std::thread recv_thread (receiveMessege, client_socket);

	send_thread.join();
	recv_thread.join();
	close(client_socket);

    clientView.displayMesseges();
    
}

int main() 
{
    ClientController controller;

    controller.requestForConnection();

}