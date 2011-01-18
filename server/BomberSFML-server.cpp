//============================================================================
// Name        : BomberSFML-server.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include "Client.h"

#include <vector>

using namespace std;

int main() {

	vector<Client*> clients;
	vector<Client*>::iterator ico;


	bool running = true;



	unsigned short listenPort = 8889;

	sf::SocketTCP listener;

	listener.Listen(listenPort);


	while(running) {

		sf::SocketTCP clientSocket;
		sf::IPAddress clientAddress;

		cout << "Waiting for connections on " << listenPort << endl;

		if(listener.Accept(clientSocket, &clientAddress) == sf::Socket::Done) {

			cout << "Incoming connection..." << endl;
			Client *c = new Client(clientSocket, clientAddress);

			clients.push_back(c);

		}

	}


	return EXIT_SUCCESS;
}
