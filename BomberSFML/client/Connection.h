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
	Connection(sf::SocketTCP *socket, unsigned int port,
			sf::IPAddress const& address, long id);

	bool isValid();
	virtual ~Connection();
	bool connect();

	std::map<long, Character> getPlayers();

	bool setPosition(Character &character);
	bool close();
	bool auth();

	sf::Mutex connectionMutex;

private:

	sf::SocketTCP *socket;
	sf::IPAddress host;
	unsigned int port;
	long id;

};

#endif /* CONNECTION_H_ */
