#include "DBOperation.h"

bool DBOperation::validateUserNameAndPassword(string userId, string password)
{
	auto collection = conn["UserDB"]["UserInfo"];
	auto cursor = collection.find({});
	bsoncxx::document::element id, pwd;

	for(auto data : cursor) 
	{
		id = data["UserID"];
		pwd = data["Password"];

		if(string(id.get_utf8().value) == userId && string(pwd.get_utf8().value) == password)
		{
			return true;
		}
	}
	return false;
}
