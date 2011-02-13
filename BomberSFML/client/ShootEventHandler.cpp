/*
 * ShootEventHandler.cpp
 *
 *  Created on: 2011-02-02
 *      Author: zapo
 */

#include "ShootEventHandler.h"
#include "Window.h"
#include "Character.h"
#include "Connection.h"

ShootEventHandler::ShootEventHandler(Character &character, Connection &connection) :
	handledCharacter(&character),
	connection(&connection) {

}

ShootEventHandler::~ShootEventHandler() {
	// TODO Auto-generated destructor stub
}

void ShootEventHandler::handle(const sf::Event &event) const {

	if( event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Space) {

		handledCharacter->setCurrentAction(Character::SHOOTING);

		connection->connectionMutex.Lock();

		connection->setPosition(*handledCharacter);

		connection->connectionMutex.Unlock();

	} else if(event.Type == sf::Event::KeyReleased && event.Key.Code == sf::Key::Space) {

		handledCharacter->setCurrentAction(Character::IDLEING);

		connection->connectionMutex.Lock();

		connection->setPosition(*handledCharacter);

		connection->connectionMutex.Unlock();

	}


}
