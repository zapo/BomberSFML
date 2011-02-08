#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include "Channel.h"
#include "Client.h"
#include "../client/Character.h"
#include "../../BomberSFML-network/Message.h"
#include <SFML/System/Mutex.hpp>
#include <vector>

using namespace std;

sf::Image Character::tankImage;

int main() {

	bool running = true;

	unsigned short listenPort = 8889;

	sf::SocketTCP listener;

	if (listener.Listen(listenPort)) {

		Channel channel;

		while (running) {

			sf::SocketTCP clientSocket;
			sf::IPAddress clientAddress;

			cout << "Waiting for connections on " << listenPort << endl;

			if (listener.Accept(clientSocket, &clientAddress)
					== sf::Socket::Done) {

				cout << "Incoming connection, getting client id..." << endl;

				sf::Packet idpacket, confirmation;

				if (clientSocket.Receive(idpacket) == sf::Socket::Done) {

					Bomber::Message authmessage;

					idpacket >> authmessage;

					Bomber::Message confMessage(authmessage.getId(),
							Bomber::MessageInfo::OK);

					if (authmessage.getId() != 0) { //need tests that assert channel doesnt already have this clientid

						std::cout << "Authentified !" << std::endl;
						confMessage.setType(Bomber::MessageInfo::OK);

					} else {

						std::cout << "NOT authentified sorry !" << std::endl;
						confMessage.setType(Bomber::MessageInfo::NOK);

					}

					confirmation << confMessage;

					if (clientSocket.Send(confirmation) == sf::Socket::Done
							&& confMessage.getType() == Bomber::MessageInfo::OK) {

						std::cout << "Adding client " << authmessage.getId()
								<< " to channel " << &channel << std::endl;
						Client *c = new Client(clientSocket, clientAddress,
								channel, authmessage.getId());
						channel.add(*c);

						c->Launch();

					}

				}

			}

		}

	}

	return EXIT_SUCCESS;
}
