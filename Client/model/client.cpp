#include "client.h"

int Client::connectToServer()
{
    int sock = 0;
    struct sockaddr_in serv_addr;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n"); 
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        printf("\nInvalid address/ Address not supported \n"); 
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n"); 
        return -1;
    } else {
        return sock;
    }
}


void Client::sendMessege(int sock)
{
    char msg[1024]; 

    memset(msg, 0, sizeof msg);
    std::cin.getline(msg, 1024);
	send(sock ,msg ,strlen(msg) ,0); 
}

void Client::receiveMessege(int sock)
{
    char buffer[1024] = {0}; 
    
    memset(buffer, 0, sizeof buffer);
	read(sock, buffer, 1024); 
	printf("Server: %s\n", buffer ); 
}