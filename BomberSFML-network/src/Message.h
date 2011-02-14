/*
 * Message.h
 *
 *  Created on: 2011-01-27
 *      Author: zapo
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <cstring>
#include <SFML/Network.hpp>
#include <iostream>

namespace Bomber {

class MessageInfo {
public:

	enum Type {
		NONE, MOVE_TO, GET_PLAYERS, OK, NOK, CLOSE
	};

	static Type toType(int _type) {

		switch (_type) {

		case MOVE_TO:
			return MOVE_TO;

		case GET_PLAYERS:
			return GET_PLAYERS;
		case OK:
			return OK;
		case NOK:
			return NOK;
		case CLOSE:
			return CLOSE;
		default:
			return NONE;

		}

	}
};

class Message {

public:

	Message(long id = 0, MessageInfo::Type type = MessageInfo::NONE);

	virtual ~Message();

	MessageInfo::Type getType();

	sf::Uint32 getId();

	void setId(sf::Uint32 id);
	void setType(MessageInfo::Type type);

private:

	sf::Uint32 id;
	MessageInfo::Type type;
};

}

using namespace Bomber;

sf::Packet& operator<<(sf::Packet &p, MessageInfo::Type &type);
sf::Packet& operator>>(sf::Packet &p, MessageInfo::Type &type);
sf::Packet& operator>>(sf::Packet &p, Message &message);
sf::Packet& operator<<(sf::Packet &p, Message &message);

#endif /* MESSAGE_H_ */
