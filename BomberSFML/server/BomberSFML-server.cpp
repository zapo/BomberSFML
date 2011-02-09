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

	unsigned short listenPort = 8890;
	unsigned short dataPort = 8889;

	sf::SocketUDP listener;

	if (listener.Bind(listenPort)) {

		Channel channel;

		while (running) {

			sf::IPAddress clientAddress;

			cout << "Waiting for authentication messages on " << listenPort
					<< endl;

			sf::Packet idpacket, confirmation;

			if (listener.Receive(idpacket, clientAddress, listenPort)
					== sf::Socket::Done) {

				Bomber::Message authmessage;
				idpacket >> authmessage;

				cout << "Incoming connection, getting client id..." << endl;

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

				if (listener.Send(confirmation, clientAddress, listenPort)
						== sf::Socket::Done && confMessage.getType()
						== Bomber::MessageInfo::OK) {

					std::cout << "Adding client " << authmessage.getId()
							<< " to channel " << &channel << std::endl;
					Client *c = new Client(dataPort, clientAddress, channel,
							authmessage.getId());
					channel.add(*c);

					c->Launch();

				}

			}

		}

	}

	return EXIT_SUCCESS;
}


