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
	void add(const Client &client);
	bool remove(long id);

	std::map<long, const Client*>& getClients();
	std::map<long, Character> getPlayers();

private:

	std::map<long, const Client*> clients;
	std::map<long, const Client*>::iterator cit;

	sf::Mutex clientsMutex;

};

#endif /* CHANNEL_H_ */
