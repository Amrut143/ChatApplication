#include "clientUtility.h"

void sendDataToServer(string message, int sockfd) {
        send(sockfd, message.c_str(), message.size() + 1, 0);
}

string readResponseFromServer(int sockfd) {
    char buffer[LENGTH] = {};
	int receive = recv(sockfd, buffer, LENGTH, 0);

    if (receive > 0) {
        printf("%s\n", buffer);
    } else if (receive == 0) {
		printf("Server Disconnected\n");
    } else {
		perror("Server ERROR");
	}
    return (string)buffer;
}