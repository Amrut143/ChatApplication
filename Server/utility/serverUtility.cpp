#include "serverUtility.h"

void* parseCommand(char* buffer, char* message, char* name) {
	int index = 0;
	int count;

	if (buffer[0] != '#') {
		name[index] = ' ';
      	return NULL;
    }
	for (count = 1; count < strlen(buffer); count++) {

		if(buffer[count] != ' ') {
			name[index++] = buffer[count];
		} else {
			name[index++] = '\0';
			break;
		}
  	}
	index = 0;
	for ( ; count < strlen(buffer); count++) {

		if(buffer[count] != '\0') {
			message[index++] = buffer[count];
		}
  	}	
	return NULL;
}

vector<string> split(const string &s, char delimeter) {
    stringstream ss(s);
    string item;
    vector<string> tokens;

    while (getline(ss, item, delimeter)) {
        tokens.push_back(item);
    }
    return tokens;
}

string splitUsers(vector<string> users_list) {
	string users = "\033[0;32m\n";
	string temp;

	for(int count = 0; count < users_list.size(); ++count) {
		temp = users_list[count];
		users +=temp;
		users += "\n";
	}
	users += "\033[0m";
	return users;
}