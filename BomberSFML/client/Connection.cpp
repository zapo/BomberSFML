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

	if (socket.Send(request, host, port) == sf::Socket::Done) {

		if (socket.Receive(response, host, port) == sf::Socket::Done) {
			response >> confirmation;

			accepted = (confirmation.getType() == MessageInfo::OK);
		}

	}

	return accepted;

}

Connection::Connection(unsigned short port,
		sf::IPAddress & address, long id) :
	host(address), port(port), id(id) {

	socket.Bind(port);

}

bool Connection::close() {

	std::cout << "Closing connection ..." << std::endl;

	sf::Packet closePacket, confPacket;

	bool closed = false;
	Message closeMessage(id, MessageInfo::CLOSE), confMessage;

	closePacket << closeMessage;

	if (socket.Send(closePacket, host, port) == sf::Socket::Done) {

		if (socket.Receive(confPacket, host, port) == sf::Socket::Done) {

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

	sf::SocketUDP authsocket;

	unsigned short port = 8890;

	std::cout << "authentication..." << std::endl;

	if(!authsocket.Bind(port)) {
		return false;
	}

	bool authenticated = false;

	sf::Packet authpacket, conf;
	Message authmessage(id), authconf;
	authpacket << authmessage;

	if (socket.Send(authpacket, host, port) == sf::Socket::Done) {

		if (authsocket.Receive(conf, host, port) == sf::Socket::Done) {

			conf >> authconf;

			authenticated = (authconf.getType() == MessageInfo::OK);

		}
	}

	authsocket.Close();

	return authenticated;

}

map<long, Character> Connection::getPlayers() {

	sf::Packet request, response;
	map<long, Character> positions;

	Message positionRequest(id, MessageInfo::GET_PLAYERS);
	DataMessage<std::map<long, Character> > positionResponse;

	request << positionRequest;

	if (socket.Send(request, host, port) == sf::Socket::Done) {

		if (socket.Receive(response, host, port) == sf::Socket::Done) {

			response >> positionResponse;

			positions = positionResponse.getData();

		}
	}

	return positions;

}

bool Connection::isValid() {
	return socket.IsValid();
}

