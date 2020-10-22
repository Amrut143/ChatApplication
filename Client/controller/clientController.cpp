#include "../model/client.h"

#define LENGTH 2048
#define VALID "0"
#define INVALID "1"


volatile sig_atomic_t flag = 0;
int sockfd = 0;
char name[32];

void catch_ctrl_c_and_exit(int sig) {
    flag = 1;
}

void sendDataToServer(string message, int sockfd)
{
        send(sockfd, message.c_str(), message.size() + 1, 0);
}

string readResponseFromServer(int sockfd)
{
    char buffer[LENGTH] = {};
	int receive = recv(sockfd, buffer, LENGTH, 0);

    if (receive > 0)
    {
        printf("%s\n", buffer);
    } else {
		printf("Server Disconnected\n");
    }
    return (string)buffer;
}


void* sendMsgHandler(void* arg) {
    char message[LENGTH] = {};
    char buffer[LENGTH + 32] = {};

    while(1) {
        fgets(message, LENGTH, stdin);
        message[strlen(message) - 1] = '\0';

        if (strcmp(message, "exit") == 0) {
		    break;
        } else {
            send(sockfd, message, strlen(message), 0);
        }
	    bzero(message, LENGTH);
        bzero(buffer, LENGTH + 32);
    }
    catch_ctrl_c_and_exit(2);
    return NULL;
}

void* recvMsgHandler(void* arg) {
    char message[LENGTH] = {};

    while (1) {
	    int receive = recv(sockfd, message, LENGTH, 0);

        if (receive > 0) {
            printf("%s\n", message);
        } else {
			break;
		}
		memset(message, 0, sizeof(message));
    }
    return NULL;
}

string login(int sockfd)
{
    string user_name, password, auth;

    cout << "Enter Your Registered Username: " << endl;
    cin >> user_name;
    cout << "Enter Password: " << endl;
    cin >> password;

    auth = "AUTHENTICATE " + user_name + " " + password;

    sendDataToServer(auth, sockfd);

    return readResponseFromServer(sockfd);
}

void requestForConnection() {
    Client client;
    signal(SIGINT, catch_ctrl_c_and_exit);


    sockfd = client.connectToServer();
    
    while(INVALID == login(sockfd)) {
	    cout<< "\033[1;31mWrong Username Or Password\033[0m\n\n";
	}
	cout<< "\033[1;32mLogin Successful.....\033[0m\n\n";
    cout<< "\033[1;32m*****Welcome To ChatRoom*****\033[0m\n\n";

    pthread_t send_msg_thread;

    if(pthread_create(&send_msg_thread, NULL, &sendMsgHandler, NULL) != 0) {
	    printf("ERROR: pthread\n");
        exit(EXIT_FAILURE);
	}
	
    pthread_t recv_msg_thread;

    if(pthread_create(&recv_msg_thread, NULL, &recvMsgHandler, NULL) != 0) {
		printf("ERROR: pthread\n");
		exit(EXIT_FAILURE);
	}

	while(1) {
		if(flag) {
			printf("\nBye\n");
			break;
        }
	}
	close(sockfd);
}

int main() {
    system("clear");
    requestForConnection();
}  