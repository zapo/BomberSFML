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
	Connection(unsigned short, sf::IPAddress & address, long id);

	bool isValid() const;
	virtual ~Connection();

	std::map<long, Character> getPlayers() ;

	bool setPosition(Character &character);
	bool close();
	bool auth();

	sf::Mutex connectionMutex;

private:

	sf::SocketUDP server;
	sf::IPAddress host;

	unsigned short authPort;
	unsigned short receivePort;
	unsigned short sendPort;
	long id;

};

#endif /* CONNECTION_H_ */
