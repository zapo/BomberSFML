/*
 * Channel.h
 *
 *  Created on: 2011-01-30
 *      Author: zapo
 */

#ifndef CHANNEL_H_
#define CHANNEL_H_

#include <map>
#include <SFML/System.hpp>

class Client;
class Character;

class Channel {
public:
	Channel();
	virtual ~Channel();
	void add(Client &client);
	bool remove(long id);

	std::map<long, Client*>& getClients();
	std::map<long, Character> getPlayers();

private:

	std::map<long, Client*> clients;
	std::map<long, Client*>::iterator cit;

	sf::Mutex clientsMutex;

};

#endif /* CHANNEL_H_ */
