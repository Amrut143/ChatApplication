#include "server.h"

int Server::establishListener() 
{ 
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{ 
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	}

	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEPORT , &opt, sizeof(opt)))
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 

	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( PORT ); 

	if (bind(server_fd, (struct sockaddr *)&address, 
								sizeof(address)) < 0) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
    
	if (listen(server_fd, 3) < 0) 
    { 
		perror("listen"); 
		exit(EXIT_FAILURE); 
	} else {
        return server_fd;
    } 
}

int Server::acceptNewConnection()
{
	new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    return new_socket;
}

void Server::sendMessage(int sock)
{
	memset(msg, 0, sizeof msg);
	cin.getline(msg, 1024);
	send(sock ,msg ,strlen(msg) ,0); 
}

void Server::recieveMessage(int sock)
{
	memset(buffer, 0, sizeof buffer);
	read(sock, buffer, 1024); 
	printf("Client: %s\n", buffer ); 
}