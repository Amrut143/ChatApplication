all: Client/controller/clientController.cpp Client/model/client.cpp Server/controller/serverController.cpp Server/model/server.cpp
	g++ --std=c++11 -pthread Client/controller/clientController.cpp Client/model/client.cpp -o client 
	g++ --std=c++11 -pthread  Server/controller/serverController.cpp Server/model/server.cpp -o server

