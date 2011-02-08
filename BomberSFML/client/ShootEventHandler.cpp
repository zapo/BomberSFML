/*
 * ShootEventHandler.cpp
 *
 *  Created on: 2011-02-02
 *      Author: zapo
 */

#include "ShootEventHandler.h"
#include "Window.h"
#include "Character.h"

ShootEventHandler::ShootEventHandler(Character &character) :
	handledCharacter(&character) {

}

ShootEventHandler::~ShootEventHandler() {
	// TODO Auto-generated destructor stub
}

void ShootEventHandler::handle(sf::Event &event) {

	if (handledWindow->GetInput().IsKeyDown(sf::Key::Space)) {

		handledCharacter->shoot();

	}

}
