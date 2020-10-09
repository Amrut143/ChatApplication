all: Client/controller/clientController.cpp Client/model/client.cpp Client/view/clientView.cpp Server/controller/serverController.cpp Server/model/server.cpp Server/view/serverView.cpp
	g++ --std=c++11 -pthread Client/controller/clientController.cpp Client/model/client.cpp Client/view/clientView.cpp -o client 
	g++ --std=c++11 -pthread  Server/controller/serverController.cpp Server/model/server.cpp Server/view/serverView.cpp -o server

