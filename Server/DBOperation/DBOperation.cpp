#include "DBOperation.h"

bool DBOperation::isUserAlreadyExists(string userId) {
	auto collection = conn["UserDB"]["UserInfo"];
	auto cursor = collection.find({});
	bsoncxx::document::element id;

	for(auto data : cursor) {
		id = data["UserID"];

		if(string(id.get_utf8().value) == userId) {
			return true;
		}
	}
	return false;
}

bool DBOperation::validateUserNameAndPassword(string userId, string password) {
	auto collection = conn["UserDB"]["UserInfo"];
	auto cursor = collection.find({});
	bsoncxx::document::element id, pwd;

	for(auto data : cursor) {
		id = data["UserID"];
		pwd = data["Password"];

		if(string(id.get_utf8().value) == userId && string(pwd.get_utf8().value) == password) {
			return true;
		}
	}
	return false;
}

void DBOperation::addUserToDB(string userId, string password) {
	auto collection = conn["UserDB"]["UserInfo"];
	auto builder = bsoncxx::builder::stream::document{};
	
	bsoncxx::document::value document = builder 
										   << "UserID" << userId
										   << "Password" << password
										   << finalize;

			 collection.insert_one(document.view());
}

void DBOperation::addMessagesToDB(string sender_name, string reciever_name, string message, string status) {
	string collection_name = getCollectionName(sender_name, reciever_name);
	auto collection = conn["UserDB"][collection_name];
	auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
	auto builder = bsoncxx::builder::stream::document{};
	
	bsoncxx::document::value document = builder 
										   << "Sender" << sender_name
										   << "Reciever" << reciever_name
										   << "Message" << message
										   << "Time" << ctime(&time)
										   << "Status" << status 
										   << finalize;

			 collection.insert_one(document.view());
}

string DBOperation::getCollectionName(string sender, string reciever) {
	if(sender < reciever)
		return sender + reciever;
	return reciever + sender;
}


vector<string> DBOperation::getUserMessages(string sender_name, string reciever_name) {
	string collection_name = getCollectionName(sender_name, reciever_name);
	auto collection = conn["UserDB"][collection_name];
	auto cursor = collection.find({});
	bsoncxx::document::element sender, reciever, msg;
	vector<string> messages;

	for(auto data : cursor) {
		sender = data["Sender"];
		msg = data["Message"];

		string message;
		if(sender_name == sender.get_utf8().value) {
			message += "\033[1;31m" + string(sender.get_utf8().value) + " :" + "\033[0;33m" + string(msg.get_utf8().value) + "\033[0m\n";
		}
		else {
			message += "\033[1;32mYou : \033[0;33m" + string(msg.get_utf8().value) + "\033[0m";
		}
		messages.push_back(message);
	}
	return messages;
}
