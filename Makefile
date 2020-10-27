all: Client/controller/clientController.cpp Client/model/client.cpp 
	g++ --std=c++17 -pthread Client/controller/clientController.cpp Client/model/client.cpp -o client 