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

class Client: public sf::Thread {
public:
	Client(sf::SocketTCP&, sf::IPAddress&);

	virtual ~Client();
	sf::Vector2<int>& getPosition();

private:
	virtual void Run();

	sf::Vector2<int> position;
	sf::SocketTCP socket;
	sf::IPAddress ipaddress;

};

#endif /* CLIENT_H_ */
