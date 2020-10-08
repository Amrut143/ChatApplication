#include "serverView.h"

void ServerView::displayServerListenMsg()
{
    cout << "*****Welcome to my chat application*****" << endl; 
    cout << "Server started. Listening...." << endl;
}

void ServerView::displayConnectionAcceptMsg()
{
    cout << "Server started. Accepting...." << endl;
    cout << "Connection Accepted. Reading....." << endl;
}