all: Client/controller/clientController.cpp   Client/model/client.cpp Client/view/clientView.cpp Server/controller/serverController.cpp Server/model/server.cpp Server/view/serverView.cpp
	g++ --std=c++11 Client/controller/clientController.cpp   Client/model/client.cpp Client/view/clientView.cpp -o client 
	g++ --std=c++11  Server/controller/serverController.cpp Server/model/server.cpp Server/view/serverView.cpp -o server

