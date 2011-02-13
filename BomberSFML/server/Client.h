/*
 * Client.h
 *
 *  Created on: 2011-01-17
 *      Author: zapo
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

class Channel;
class Character;

class Client: public sf::Thread {
public:
	Client(const unsigned int, const unsigned int, sf::SocketUDP&, sf::IPAddress&, Channel& channel, sf::Uint32 id);
	long getId() const;

	virtual ~Client();
	Character& getPlayer() const;

private:
	virtual void Run();

	Character *character;
	sf::SocketUDP *socket;
	sf::IPAddress ipaddress;
	Channel* channel;

	short unsigned int sendPort;
	short unsigned int receivePort;

	long id;
};

#endif /* CLIENT_H_ */
