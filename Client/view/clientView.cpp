#include "clientView.h"

string ClientView::login(int sockfd) {
    string user_name, password, auth;

    cout<< "\033[1;34mEnter Your Registered Username: \033[0m";
    cin >> user_name;
    cout << "\033[1;34mEnter Password: \033[0m";
    cin >> password;

    auth = "AUTHENTICATE " + user_name + " " + password;
    user_id = user_name;

    sendDataToServer(auth, sockfd);

    return readResponseFromServer(sockfd);
}

string ClientView::registration(int sockfd) {
    string user_name, password, conformPwd, auth;

        cout << "\033[1;34mEnter Username: \033[0m";
        cin >> user_name;
        cout << "\033[1;34mEnter Password: \033[0m";
        cin >> password;

    while(conformPwd != password) {
        cout << "\033[1;34mConform Password: \033[0m";
        cin >> conformPwd;
    }

    auth = "REGISTER " + user_name + " " + password;

    sendDataToServer(auth, sockfd);

    return readResponseFromServer(sockfd);
}

bool ClientView::registrationAndLogin(int sockfd) {

    bool exit_flag = true;
    int option; 

    cout << "\033[1;33m********Select Option********\033[0m\n\n";
    cout << "\033[1;35m1.Login \n2.Registration\033[0m\n\n";
    cin >> option;
    while(exit_flag) {
        switch (option) {
            case LOGIN:
		        while(INVALID == login(sockfd)) {
	    	        cout<<"\033[1;31mWrong Username Or Password\033[0m\n\n";
		        }
                system("clear");
		        cout<<"\033[1;32mLogin Successfully......\033[0m\n\n";
                exit_flag = false;
                break;

            case REGISTRATION:
		        while(VALID == registration(sockfd)) {
			        cout<<"\033[1;31mYour username has already been registered. Please try again\033[0m\n\n" << endl;
		        }
                system("clear");
		        cout<<"\033[1;32mRegister Successfully.......\033[0m\n\n";
                cout << "\033[1;33m********Login To Your Account********\033[0m\n\n";
                option = LOGIN;
                break;
                
            default:
                cout << "Invalid Input" << endl;
                exit_flag = false;
                break;
        }
    }
    return exit_flag;
}

void ClientView::displayMenu() {
    cout << "\033\t[1;33mWelcome To Chat App\033[0m\n\n";
    cout << "\033[3;42;30mONLINE-" << user_id << "\033[0m\t\t\n";
    cout << "\033\n[1;36mUse Following Commands\033[0m\n\n";
    cout << "\033[1;35m -----------------------------------\n"
                 << "|[online] View online users         |\n"
                 << "|[allmsg user_name] view all msgs   |\n"
                 << "|[unseenmsg user_name] unseen msg   |\n"
                 << "|[#user_name msg] Msg to single user|\n"
                 << " -----------------------------------\n\033[0m";
}