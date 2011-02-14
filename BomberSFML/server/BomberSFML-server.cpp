#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include "Channel.h"
#include "Client.h"
#include "../client/Character.h"
#include "../../BomberSFML-network/src/Message.h"
#include <SFML/System/Mutex.hpp>
#include <vector>

using namespace std;

int main() {

	bool running = true;

	unsigned short listenPort = 7000;


	sf::SocketUDP listener;

	if (listener.Bind(listenPort)) {

		Channel channel;

		while (running) {

			sf::IPAddress clientAddress;

			cout << "Waiting for authentication messages on " << listenPort
					<< endl;

			sf::Packet idpacket, confirmation;

			unsigned short clientPort;
			if (listener.Receive(idpacket, clientAddress, clientPort) == sf::Socket::Done) {

				Bomber::Message authmessage;
				idpacket >> authmessage;

				cout << "Incoming connection from " << clientAddress << ", getting client id..." << endl;

				Bomber::Message confMessage(authmessage.getId(),
						Bomber::MessageInfo::OK);

				if (authmessage.getId() > 0) { //need tests that assert channel doesnt already have this clientid

					std::cout << "Authenticated !" << std::endl;
					confMessage.setType(Bomber::MessageInfo::OK);

				} else {

					std::cout << "NOT authenticated sorry !" << std::endl;
					confMessage.setType(Bomber::MessageInfo::NOK);

				}

				confirmation << confMessage;

				sf::SocketUDP* clientSocket = new sf::SocketUDP();

				int randomport = 0;

				do {

					randomport = sf::Randomizer::Random(7001, 7100);

				} while(!clientSocket->Bind(randomport));

				if (clientSocket->Send(confirmation, clientAddress, clientPort) == sf::Socket::Done && confMessage.getType() == Bomber::MessageInfo::OK) {

					// TODO check if same user don't exist in client list with same port & address

					std::cout

					<< "Adding client " 		<< authmessage.getId()
					<< " connected with port " 	<< clientPort
					<< " to channel "  			<< &channel
					<< " on " 					<< randomport
					<< std::endl;


					Client *c = new Client(clientPort, randomport, *clientSocket, clientAddress, channel, authmessage.getId());

					channel.add(*c);

					c->Launch();

				}

			}

		}

	}

	return EXIT_SUCCESS;
}


