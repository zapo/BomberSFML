/*
 * Connection.h
 *
 *  Created on: 2011-01-17
 *      Author: zapo
 */

#ifndef CONNECTION_H_
#define CONNECTION_H_

#include <SFML/Network.hpp>
#include <SFML/System.hpp>

class Connection : sf::Thread {
public:
	Connection(sf::SocketTCP& sock, unsigned int port, sf::IPAddress const& address);

	virtual void Run();
	bool isConnected();
	virtual ~Connection();

private:
	bool connect();
	sf::SocketTCP socket;
	sf::IPAddress host;
	unsigned int port;

};

#endif /* CONNECTION_H_ */
