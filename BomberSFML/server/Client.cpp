/*
 * Client.cpp
 *
 *  Created on: 2011-01-17
 *      Author: zapo
 */

#include "Client.h"
#include "Channel.h"
#include "../client/Character.h"

#include <iostream>
#include <map>
#include <ctime>
#include <SFML/Network.hpp>
#include "../../BomberSFML-network/DataMessage.h"
#include "../../BomberSFML-network/Message.h"

using namespace Bomber;
using namespace std;

extern sf::Mutex clientsMutex;

namespace boost {

namespace serialization {
template<class Archive>
void serialize(Archive &ar, sf::Vector2<float> &vector,
		const unsigned int version) {

	ar & vector.x;
	ar & vector.y;

}
}

}

Client::Client(sf::SocketTCP &socket, sf::IPAddress &ipaddress,
		Channel &channel, sf::Uint32 id) :
	id(id), channel(&channel), socket(socket), ipaddress(ipaddress),
			sf::Thread() {

	sf::Randomizer::SetSeed( time(NULL));

	character = new Character(id);
	character->SetPosition(sf::Vector2f(sf::Randomizer::Random(0, 800),
			sf::Randomizer::Random(0, 600)));
	character->setOrientation(Character::DOWN);
}

Client::~Client() {
	delete character;
}

Character& Client::getPlayer() {
	return *character;
}

long Client::getId() {
	return id;
}

void Client::Run() {

	cout << "New client on address " << ipaddress << endl;

	sf::Packet request, response;

	while (socket.Receive(request) == sf::Socket::Done) {

		Message requestMessage;

		request >> requestMessage;

		if (requestMessage.getId() == id) {

			switch (requestMessage.getType()) {

			case MessageInfo::GET_PLAYERS: {

				map<long, Character> players = channel->getPlayers();

				DataMessage<map<long, Character> > datamessage(players);

				response << datamessage;

				if (socket.Send(response) != sf::Socket::Done) {
					//throw new exception or so
				}

				break;
			}

			case MessageInfo::MOVE_TO: {

				Message conf(id, MessageInfo::NOK);
				DataMessage<Character> moveToData;

				if (request >> moveToData) {

					Character copy = moveToData.getData();

					// tests goes here

					map<long, Character> players = channel->getPlayers();
					map<long, Character>::iterator pit;

					MessageInfo::Type type = MessageInfo::OK;

					bool fit = true;

					for (pit = players.begin(); pit != players.end(); pit++) {

						if (pit->second.getId() == copy.getId())
							continue;

					}

					*character = copy;

					conf.setType(MessageInfo::OK);

				}

				response << conf;

				if (socket.Send(response) == sf::Socket::Done) {

				}
				break;
			}

			case MessageInfo::CLOSE: {

				MessageInfo::Type type =
						(channel->remove(id)) ? MessageInfo::OK
								: MessageInfo::NOK;

				Message conf(id, type);

				response << conf;

				if (!socket.Send(response) == sf::Socket::Done) {
					//exception
				}

				break;
			}

			}

		}

		request.Clear();
		response.Clear();

	}

}
