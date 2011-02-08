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

bool Connection::setPosition(Character &character) {

	bool accepted = false;
	sf::Packet request, response;

	Message moveTo(id, MessageInfo::MOVE_TO), confirmation;
	DataMessage<Character> moveToData(character);

	request << moveTo << moveToData;

	if (socket->Send(request) == sf::Socket::Done) {

		if (socket->Receive(response) == sf::Socket::Done) {
			response >> confirmation;

			accepted = (confirmation.getType() == MessageInfo::OK);
		}

	}

	return accepted;

}

Connection::Connection(sf::SocketTCP *socket, unsigned int port,
		sf::IPAddress const& address, long id) :
	host(address), port(port), socket(socket), id(id) {

}

bool Connection::close() {

	std::cout << "Closing connection ..." << std::endl;

	sf::Packet closePacket, confPacket;

	bool closed = false;
	Message closeMessage(id, MessageInfo::CLOSE), confMessage;

	closePacket << closeMessage;

	if (socket->Send(closePacket) == sf::Socket::Done) {

		if (socket->Receive(confPacket) == sf::Socket::Done) {

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

	if (socket->Send(authpacket) == sf::Socket::Done) {

		if (socket->Receive(conf) == sf::Socket::Done) {

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

	if (socket->Send(request) == sf::Socket::Done) {

		if (socket->Receive(response) == sf::Socket::Done) {

			response >> positionResponse;

			positions = positionResponse.getData();

		}
	}

	return positions;

}

bool Connection::connect() {

	cout << "Trying to connect to server " << host << " ..." << endl;
	cout.flush();

	return (socket->Connect(port, host) == sf::Socket::Done && (cout << "Done"
			<< endl));
}

bool Connection::isValid() {
	return socket->IsValid();
}

