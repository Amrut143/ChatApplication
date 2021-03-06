#include "onlineUsers.h"

User *users[MAX_USERS];
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

void addUser(User *user) {
	pthread_mutex_lock(&clients_mutex);

	for(int count = 0; count < MAX_USERS; ++count) {
		if(!users[count]) {
			users[count] = user;
			break;
		}
	}
	pthread_mutex_unlock(&clients_mutex);
}

void removeUser(int user_id) {
	pthread_mutex_lock(&clients_mutex);

	for(int count = 0; count < MAX_USERS; ++count) {
		if(users[count]) {
			if(users[count]->user_id == user_id) {
				users[count] = NULL;
				break;
			}
		}
	}
	pthread_mutex_unlock(&clients_mutex);
}

void sendMessage(char* message, int user_id)
{
	pthread_mutex_lock(&clients_mutex);

	for(int count = 0; count < MAX_USERS; ++count){
		if(users[count]) {
			if(users[count]->user_id != user_id) {
				if(write(users[count]->sock_fd, message, strlen(message)) < 0) {
					perror("ERROR: write to descriptor failed");
					break;
				}
			}
		}
	}
	pthread_mutex_unlock(&clients_mutex);
}

void sendMessageToParticularUser(char* s,const char* name) {
	pthread_mutex_lock(&clients_mutex);

	for(int count = 0; count < MAX_USERS; ++count) {
		if(users[count]) {
			if ((users[count]->user_name.compare(name)) == 0 ) {
				if(write(users[count]->sock_fd, s, strlen(s)) < 0) {
					perror("ERROR: write to descriptor failed");
					break;
				}
			}
		}
	}
	pthread_mutex_unlock(&clients_mutex);
}

vector<string> getOnlineUsers(string name) {
	pthread_mutex_lock(&clients_mutex);
	vector<string> online_users;

	for(int count = 0; count <MAX_USERS;++count) {
		if(users[count]) {
			if(users[count]->user_name != name) {
				online_users.push_back(users[count]->user_name);
			}
		}
	}
	pthread_mutex_unlock(&clients_mutex);
	return online_users;
}

bool isUserOnline(string name) {
	pthread_mutex_lock(&clients_mutex);
	bool flag = false;

	for(int count = 0; count < MAX_USERS; ++count) {
		if(users[count]) {
			if(users[count]->user_name == name) {
				flag = true;
				break;
			}
		}
	}
	pthread_mutex_unlock(&clients_mutex);
	return flag;
}