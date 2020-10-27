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
										   << bsoncxx::builder::stream::finalize;

			 collection.insert_one(document.view());
}
