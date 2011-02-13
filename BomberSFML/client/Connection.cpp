/*
 * Connection.cpp
 *
 *  Created on: 2011-01-17
 *      Author: zapo
 */

#include "Connection.h"
#include "Character.h"
#include "../../BomberSFML-network/DataMessage.h"
#include "../../BomberSFML-network/Message.h"
#include <iostream>
#include <map>

using namespace std;
using namespace Bomber;

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

Connection::Connection(const unsigned short authPort, const sf::IPAddress & address, const long id) :
	host(address), authPort(authPort), receivePort(receivePort), id(id) {

	do {

	receivePort = sf::Randomizer::Random(7101, 7201);

	} while(!server.Bind(receivePort));
}

bool Connection::setPosition(const Character &character) {

	bool accepted = false;
	sf::Packet request, response;

	Message moveTo(id, MessageInfo::MOVE_TO), confirmation;
	DataMessage<Character> moveToData(character);

	request << moveTo << moveToData;

	if (server.Send(request, host, sendPort) == sf::Socket::Done) {

		if (server.Receive(response, host, sendPort) == sf::Socket::Done) {
			response >> confirmation;

			accepted = (confirmation.getType() == MessageInfo::OK);
		}

	}

	return accepted;

}

bool Connection::close() {

	std::cout << "Closing connection ..." << std::endl;

	sf::Packet closePacket, confPacket;

	bool closed = false;
	Message closeMessage(id, MessageInfo::CLOSE), confMessage;

	closePacket << closeMessage;

	if (server.Send(closePacket, host, sendPort) == sf::Socket::Done) {

		if (server.Receive(confPacket, host, sendPort) == sf::Socket::Done) {

			confPacket >> confMessage;

			closed = (confMessage.getType() == MessageInfo::OK);
		}

	}

	std::cout << ((closed) ? "Connection successfully closed with server"
			: "A problem occurred while closing connection to server ")
			<< std::endl;

	return closed;

}

Connection::~Connection() {

	if (!close()) {

		//throw new exception

	}

}

bool Connection::auth() {

	bool authenticated = false;

	sf::Packet authpacket, conf;
	Message authmessage(id), authconf;
	authpacket << authmessage;


	if (server.Send(authpacket, host, authPort) == sf::Socket::Done) {

		if (server.Receive(conf, host, sendPort) == sf::Socket::Done) {

			conf >> authconf;

			authenticated = (authconf.getType() == MessageInfo::OK);

		}
	}

	return authenticated;

}

map<long, Character> Connection::getPlayers() {

	sf::Packet request, response;
	map<long, Character> positions;

	Message positionRequest(id, MessageInfo::GET_PLAYERS);
	DataMessage<std::map<long, Character> > positionResponse;

	request << positionRequest;

	if (server.Send(request, host, sendPort) == sf::Socket::Done) {

		if (server.Receive(response, host, sendPort) == sf::Socket::Done) {

			response >> positionResponse;

			positions = positionResponse.getData();

		}
	}

	return positions;

}

bool Connection::isValid() const{
	return server.IsValid();
}

