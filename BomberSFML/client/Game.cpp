/*
 * Game.cpp
 *
 *  Created on: 2011-01-30
 *      Author: zapo
 */

#include "Game.h"
#include "Window.h"
#include "Connection.h"
#include "Character.h"

#include <iostream>

Game::Game(Window &window, Connection &connection) :
	window(&window), connection(&connection), isRunning(false) {

}

Game::~Game() {

	delete connection;
	delete window;

}

void Game::loadRessources() {
	Character::init_static();
}

Character& Game::getMainCharacter() {
	return *mainCharacter;
}

void Game::setMainCharacter(Character &mainCharacter) {
	this->mainCharacter = &mainCharacter;
}

void Game::addCharacter(long id, Character &character) {

	if (!hasCharacter(id)) {

		character.init_dynamic();

		characters[id] = &character;


		window->addDrawableObject((sf::Drawable*) &character);
		std::cout << "Character " << id << " added to game"
				<< std::endl;
	}
}

void Game::deleteCharacter(long id) {
	if(hasCharacter(id)) {

		std::cout << "Deleting character " << id << std::endl;
		window->removeDrawableObject(characters[id]);

		characters.erase(id);

	}
}


bool Game::hasCharacter(long id) {

	bool haschar = (characters.find(id) != characters.end());

	return haschar;

}

Window& Game::getWindow() {
	return *window;
}

Connection& Game::getConnection() {
	return *connection;
}

void Game::setIsRunning(bool running) {
	isRunning = running;
}

void Game::run() {

	isRunning = true;

	if (connection->auth()) {

		std::cout << "Authenticated !" << std::endl;

		while (isRunning) {

			sf::Sleep(0.050);

			connection->connectionMutex.Lock();

			map<long, Character> positions = connection->getPlayers();

			connection->connectionMutex.Unlock();

			map<long, Character>::iterator pit;


			for (pit = positions.begin(); pit != positions.end(); pit++) {

				if (hasCharacter(pit->first)) {

					*characters[pit->first] = pit->second;

					Character *current = characters[pit->first];


				} else {

					Character *c = new Character(pit->second);
					addCharacter(pit->first, *c);

				}

			}

			if(characters.size() > positions.size()) {
				map<long, Character*>::iterator ppit;

				for(ppit = characters.begin(); ppit != characters.end(); ppit++) {

					if(positions.find(ppit->first) == positions.end()) {
						deleteCharacter(ppit->first);
					}

				}
			}

		}

	}

}
