#include "clientController.h"


void ClientController::sendMessege(int sock)
{
	char msg[1024]; 

	while(true)
    {
		memset(msg, 0, sizeof msg);
		std::cin.getline(msg, 1024);
		send(sock ,msg ,strlen(msg) ,0); 
	}
    
}

void ClientController::receiveMessege(int sock)
{
	char buffer[1024] = {0}; 

	while(true)
    {
		memset(buffer, 0, sizeof buffer);
		read(sock, buffer, 1024); 
		printf("Server: %s\n", buffer ); 
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