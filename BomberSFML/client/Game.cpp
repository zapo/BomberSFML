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
	window(&window), connection(&connection) {

}

Game::~Game() {

	delete connection;
	delete window;

}

void Game::loadRessources() {
	Character::init_static();
}

const Character& Game::getMainCharacter() const {
	return *mainCharacter;
}

void Game::setMainCharacter(const Character &mainCharacter) {
	this->mainCharacter = &mainCharacter;
}

void Game::addCharacter(long id, Character &character) {

	if (!hasCharacter(id)) {

		character.init_dynamic();

		characters[id] = &character;

		window->addDrawableObject(character, 2);
		std::cout << "Character " << id << " added to game" << std::endl;
	}
}

void Game::deleteCharacter(long id) {
	if (hasCharacter(id)) {

		std::cout << "Deleting character " << id << std::endl;
		window->removeDrawableObject(*(characters[id]), 2);

		characters.erase(id);

	}
}

bool Game::hasCharacter(long id) const {

	bool haschar = (characters.find(id) != characters.end());

	return haschar;

}

Window& Game::getWindow() const {
	return *window;
}

Connection& Game::getConnection() const {
	return *connection;
}

void Game::run() {

	sf::Image mapImage;
	sf::Sprite mapSprite;

	mapImage.LoadFromFile("build/client/resources/map.png");
	mapSprite.SetImage(mapImage);
	mapSprite.Resize(sf::Vector2f(1024*2, 768*2));

	window->addDrawableObject(mapSprite, 1);

	window->Launch();



	if (connection->auth()) {

		std::cout << "Authenticated !" << std::endl;

		while (window->IsOpened()) {

			sf::Sleep(0.01);

			connection->connectionMutex.Lock();

			std::map<long, Character> positions = connection->getPlayers();

			connection->connectionMutex.Unlock();

			std::map<long, Character>::iterator pit;



			for (pit = positions.begin(); pit != positions.end(); pit++) {

				if (hasCharacter(pit->first)) {

					window->drawableObjectsMutex.Lock();

					*characters[pit->first] = pit->second;

					window->drawableObjectsMutex.Unlock();

				} else {

					Character *c = new Character(pit->second);
					addCharacter(pit->first, *c);
				}

			}

			if (characters.size() > positions.size()) {
				std::map<long, Character*>::iterator ppit;

				for (ppit = characters.begin(); ppit != characters.end(); ppit++) {

					if (positions.find(ppit->first) == positions.end()) {
						deleteCharacter(ppit->first);
					}

				}
			}


			sf::Vector2f viewCenter = mainCharacter->GetPosition();

			if(mainCharacter->GetPosition().x <= window->GetWidth() / 2) {
				viewCenter.x = window->GetWidth() / 2;
			}

			if(mainCharacter->GetPosition().x >= (mapSprite.GetSize().x - window->GetWidth() / 2)) {
				viewCenter.x = (mapSprite.GetSize().x - window->GetWidth() / 2);
			}

			if(mainCharacter->GetPosition().y <= window->GetHeight() / 2) {
				viewCenter.y = window->GetHeight() / 2;
			}

			if(mainCharacter->GetPosition().y >= (mapSprite.GetSize().y - window->GetHeight() / 2)) {
				viewCenter.y = (mapSprite.GetSize().y - window->GetHeight() / 2);
			}

			window->GetDefaultView().SetCenter(viewCenter);

		}

	}

	window->Wait();

}
