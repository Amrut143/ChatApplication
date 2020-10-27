#include "../model/client.h"
#include "../view/clientView.h"

volatile sig_atomic_t flag = 0;
int sockfd = 0;
Client client;
ClientView clientView;

void catch_ctrl_c_and_exit(int sig) {
    flag = 1;
}

void* sendMsgHandler(void* arg) {
    char message[LENGTH] = {};

    while(1) {
        fgets(message, LENGTH, stdin);
        message[strlen(message) - 1] = '\0';

        if (strcmp(message, "exit") == 0) {
		    break;
        } else {
            send(sockfd, message, strlen(message), 0);
        }
	    bzero(message, LENGTH);
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
        } else if (receive == 0) {
			break;
		}
        else {
            perror("Server ERROR");
        }
		memset(message, 0, sizeof(message));
    }
    return NULL;
}

void requestForConnection() {
    signal(SIGINT, catch_ctrl_c_and_exit);

    sockfd = client.connectToServer();

    if(!clientView.registrationAndLogin(sockfd))
        clientView.displayMenu();

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

    return 0;
}  