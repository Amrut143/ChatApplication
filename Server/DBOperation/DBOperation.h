#pragma once
#include <iostream>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/builder/stream/array.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>

#include "../model/user.h"
#include <string>

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

using namespace std;

class DBOperation
{
    mongocxx::instance inst{};
    mongocxx::client conn{mongocxx::uri{}};

    public:
        bool isUserAlreadyExists(string);
        bool validateUserNameAndPassword(string, string);
        void addUserToDB(string, string);
        void addMessagesToDB(string, string, string, string);
        string getCollectionName(string, string); 
};
