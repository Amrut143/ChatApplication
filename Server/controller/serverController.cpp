#include "../model/server.h"
#include <vector>
#include <sstream>

#define BUFFER_SIZE 2048

int client_count = 0;
Server server;

void* parse(char* buffer, char* message, char* name)
{
	int index = 0;
	int i;

	if (buffer[0] != '#' )
    {
		name[index] = ' ';
      	return NULL;
    }
	
	for ( i = 1; i < strlen(buffer); i++)
    {
		if(buffer[i] != ' ')
        {
			name[index++] = buffer[i];
		} else {
			name[index++] = '\0';
			break;
		}
  	}
	index = 0;
	for ( ; i < strlen(buffer); i++)
    {
		if(buffer[i] != '\0')
        {
			message[index++] = buffer[i];
		}
  	}	
	return NULL;
}

void* handleTCPClient(void* arg)
{
    char buffer[BUFFER_SIZE];
	char buffer_to_all[BUFFER_SIZE];
    char message[BUFFER_SIZE];
	char name[32];
	int exit_flag = 0;

	client_count++;
	User* user = (User*)arg;

	if(recv(user->sock_fd, buffer, 32, 0) <= 0 )
    {
		exit_flag = 1;
	} else {
		cout << buffer << endl;
		server.sendMessage(buffer, user->user_id);
	}
	bzero(buffer, BUFFER_SIZE);

	while(1)
    {
		if (exit_flag)
        {
			break;
		}
		int receive = recv(user->sock_fd, buffer, BUFFER_SIZE, 0);
		if (receive > 0)
        {
			strcpy(buffer_to_all, user->user_name.c_str());
			strcat(buffer_to_all, " : ");
			strcat(buffer_to_all, buffer);

			if(strlen(buffer) > 0)
            {
				parse(buffer, message, name);
				bzero(buffer, BUFFER_SIZE);
			    strcpy(buffer, user->user_name.c_str());
				strcat(buffer, " : ");
				strcat(buffer, message);
				if(name[0] == ' ')
                {
					server.sendMessage(buffer_to_all, user->user_id);
				} else {
					server.sendMessageToParticularUser(buffer, name);
				}
			}
		} else if (receive == 0 || strcmp(buffer, "exit") == 0){
			sprintf(buffer, "%s has left", user->user_name.c_str());
            cout << buffer << endl;
			server.sendMessage(buffer, user->user_id);
			exit_flag = 1;
		} else {
			printf("ERROR: -1\n");
			exit_flag = 1;
		}
		bzero(buffer, BUFFER_SIZE);
		bzero(message, BUFFER_SIZE);
	}

	close(user->sock_fd);
    server.removeUser(user->user_id);
    delete user;
    client_count--;
    pthread_detach(pthread_self());

	return NULL;
}

void startServer()
{
    int socket = server.getClientSocket();
    pthread_t thread_id;

    while(true)
    {
        User* user = server.acceptNewConnection(socket);

		server.addUser(user);
        pthread_create(&thread_id, NULL, &handleTCPClient, (void*)user);

        sleep(1);
    }
    close(socket);
}

int main()
{
	system("clear");
	startServer();

	return 0;
}