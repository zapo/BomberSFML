/*
 * Client.cpp
 *
 *  Created on: 2011-01-17
 *      Author: zapo
 */

#include "Client.h"

#include <iostream>
#include <map>
#include <ctime>

Client::Client(sf::SocketTCP &socket, sf::IPAddress &ipaddress) : socket(socket), ipaddress(ipaddress), sf::Thread() {

	sf::Randomizer::SetSeed(time(NULL));

	position.x = sf::Randomizer::Random(0, 800);
	position.y = sf::Randomizer::Random(0, 600);

	this->Launch();
}

sf::Vector2<int>& Client::getPosition() {

	return position;

}

Client::~Client() {
	// TODO Auto-generated destructor stub
}

void Client::Run() {

	std::cout << "New client on address " << ipaddress << std::endl;

	//send client position throught the socket

	sf::Packet pposition;

	sf::Uint16 x = position.x;
	sf::Uint16 y = position.y;

	pposition << x << y;

	if(socket.Send(pposition) == sf::Socket::Done) {
		std::cout << "Sent : " << x << " and " << y << std::endl;
	}

}
