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
#include <vector>

using namespace std;

int main() {


	bool running = true;

	sf::IPAddress servAddr = sf::IPAddress::LocalHost;
	unsigned short listenPort = 8889;

	sf::SocketTCP listener;

	listener.Listen(listenPort);

	sf::SelectorTCP selector;

	selector.Add(listener);

	while(running) {

		unsigned int nbSockets = selector.Wait();

		for(unsigned int i = 0; i < nbSockets; i++) {

			sf::SocketTCP readySock = selector.GetSocketReady(i);

			if(readySock == listener) {

				sf::IPAddress address;
				sf::SocketTCP client;

				listener.Accept(client, &address);
				std::cout << "Client connected ! (" << address << ")" << std::endl;

				selector.Add(client);

			} else {

				sf::Packet packet;

				if(readySock.Receive(packet) == sf::Socket::Done) {

					std::string message;

					packet >> message;

					std::cout << "A client says \"" << message << "\"" <<endl;

					if(message == "HELLO") {

						sf::Packet sendback;

						std::string message = "OLLEH";

						sendback << message;

						readySock.Send(sendback);
					}

				} else {
					selector.Remove(readySock);
				}


			}

		}

	}







	return 0;
}
