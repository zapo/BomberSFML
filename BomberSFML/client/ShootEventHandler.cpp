/*
 * ShootEventHandler.cpp
 *
 *  Created on: 2011-02-02
 *      Author: zapo
 */

#include "ShootEventHandler.h"
#include "Game.h"
#include "Character.h"
#include "Connection.h"

ShootEventHandler::ShootEventHandler() {
	eventTypes.push_back(sf::Event::KeyPressed);
	eventTypes.push_back(sf::Event::KeyReleased);
}

ShootEventHandler::~ShootEventHandler() {
	// TODO Auto-generated destructor stub
}

void ShootEventHandler::handle(const sf::Event &event) {

	Character & character = game->getMainCharacter();
	Connection & connection = game->getConnection();

	if( event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Space) {

		character.setCurrentAction(Character::SHOOTING);

		connection.connectionMutex.Lock();

		connection.setPosition(character);

		connection.connectionMutex.Unlock();

	} else if(event.Type == sf::Event::KeyReleased && event.Key.Code == sf::Key::Space) {

		character.setCurrentAction(Character::IDLEING);

		connection.connectionMutex.Lock();

		connection.setPosition(character);

		connection.connectionMutex.Unlock();

	}


}
