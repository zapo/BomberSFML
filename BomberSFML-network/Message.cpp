
#include "Message.h"

namespace Bomber {

Message::Message(long id, MessageInfo::Type type) :
	id(id), type(type){
}

MessageInfo::Type Message::getType() {
	return type;
}

sf::Uint32 Message::getId() {
	return id;
}

void Message::setId(sf::Uint32 id) {
	this->id = id;
}

void Message::setType(MessageInfo::Type type) {
	this->type = type;
}

Message::~Message() {
}


}

using namespace Bomber;

sf::Packet& operator<<(sf::Packet &p, Message &message) {

	p << message.getId();
	p << message.getType();

	return p;
}

sf::Packet& operator>>(sf::Packet &p, Message &message) {

	sf::Uint32 id;
	MessageInfo::Type type;

	p >> id;
	p >> type;

	message.setId(id);
	message.setType(type);

	return p;

}


sf::Packet& operator<<(sf::Packet &p, MessageInfo::Type &type) {

	p << (sf::Uint32)type;

	return p;

}

sf::Packet& operator>>(sf::Packet &p, MessageInfo::Type &type) {

	sf::Uint32 _type;
	p >> _type;

	type = MessageInfo::toType(_type);

	return p;
}
