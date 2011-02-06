/*
 * Channel.cpp
 *
 *  Created on: 2011-01-30
 *      Author: zapo
 */

#include "Channel.h"
#include "Client.h"
#include "../client/Character.h"
#include <vector>

Channel::Channel() {
	// TODO Auto-generated constructor stub

}

Channel::~Channel() {
	// TODO Auto-generated destructor stub
}

void Channel::add(Client &client) {

	clientsMutex.Lock();

	if(clients.find(client.getId()) == clients.end()) {
		clients[client.getId()] = &client;
	}

	clientsMutex.Unlock();

}

bool Channel::remove(long id) {

	clientsMutex.Lock();

	bool removed = false;

	if(clients.find(id) != clients.end()) {

		delete(clients[id]);

		if(clients.erase(id) > 0) {
			removed = true;
		}
	}


	clientsMutex.Unlock();

	return removed;

}

std::map<long, Client*>& Channel::getClients() {

	clientsMutex.Lock();

	std::map<long, Client*>& _clients = clients;

	clientsMutex.Unlock();

	return _clients ;

}

std::map<long, Character> Channel::getPlayers() {

	clientsMutex.Lock();

	std::map<long, Character> positions;

	for (cit = clients.begin(); cit != clients.end(); cit++) {

		positions[cit->first] = cit->second->getPlayer();

	}
	clientsMutex.Unlock();

	return positions;
}
