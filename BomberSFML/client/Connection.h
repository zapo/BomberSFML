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
	Connection(const unsigned short, const sf::IPAddress & address, const long id);

	bool isValid() const;
	virtual ~Connection();

	std::map<long, Character> getPlayers() ;

	bool setPosition(const Character &character);
	bool close();
	bool auth();

	float getLatency() const;

	sf::Mutex connectionMutex;

private:

	sf::SocketUDP server;
	sf::IPAddress host;

	const unsigned short authPort;
	unsigned short receivePort;
	unsigned short sendPort;
	const long id;

	sf::Clock latencyClock;
	float latency;

};

#endif /* CONNECTION_H_ */
