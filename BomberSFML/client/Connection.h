/*
 * Connection.h
 *
 *  Created on: 2011-01-17
 *      Author: zapo
 */

#ifndef CONNECTION_H_
#define CONNECTION_H_

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

class Character;

class Connection {
public:
	Connection(unsigned short port,
			sf::IPAddress & address, long id);

	bool isValid();
	virtual ~Connection();

	std::map<long, Character> getPlayers();

	bool setPosition(Character &character);
	bool close();
	bool auth();

	sf::Mutex connectionMutex;

private:

	sf::SocketUDP socket;
	sf::IPAddress host;
	unsigned short port;
	long id;

};

#endif /* CONNECTION_H_ */
