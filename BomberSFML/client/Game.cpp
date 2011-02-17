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
#include "EventHandler.h"

#include <iostream>
#include <sstream>

sf::Image Game::mapImage;

Game::Game(Window &window, Connection &connection) :
	window(&window),
	connection(&connection),
	isLatencyPrinted(false),
	latencyRefresh(1),
	isFrameratePrinted(false),
	framerateRefresh(1) {

}

Game::~Game() {
}

void Game::loadRessources() {

	init_static();
	Character::init_static();

	mapSprite.SetImage(mapImage);
	mapSprite.Resize(sf::Vector2f(1024*2, 768*2));
}

Character& Game::getMainCharacter() const {
	return *mainCharacter;
}

void Game::setMainCharacter(Character &mainCharacter) {
	this->mainCharacter = &mainCharacter;
}

void Game::addCharacter(long id, Character &character) {

	if (!hasCharacter(id)) {

		character.init_dynamic();

		window->drawableObjectsMutex.Lock();

		characters[id] = &character;

		window->GetMainLayer().addObject(character, 2);

		window->drawableObjectsMutex.Unlock();

		std::cout << "Character " << id << " added to game" << std::endl;
	}
}

void Game::deleteCharacter(long id) {
	if (hasCharacter(id)) {

		std::cout << "Deleting character " << id << std::endl;
		window->GetMainLayer().removeObject((*(characters[id])));

		characters.erase(id);

	}
}

bool Game::hasCharacter(long id) const {

	bool haschar = (characters.find(id) != characters.end());

	return haschar;

}

void Game::addEventHandler(EventHandler & eventHandler) {

	if(window != NULL) {
		eventHandler.setGame(*this);
		window->addEventHandler(eventHandler);
	}

}

Window& Game::getWindow() const {
	return *window;
}

Connection& Game::getConnection() const {
	return *connection;
}

void Game::run() {

	window->GetMainLayer().addObject(mapSprite, 0);

	addCharacter(getMainCharacter().getId(), getMainCharacter());

	if(isFrameratePrinted) {
		window->GetInterfaceLayer().addObject(framerate, 1);
	}

	if(isLatencyPrinted) {
		window->GetInterfaceLayer().addObject(latency, 1);
	}

	window->Launch();

	if (connection->auth()) {

		std::cout << "Authenticated !" << std::endl;

		while (window->IsOpened()) {

			//main game loop

			sf::Sleep(0.01);

			updateCharacters();
			updateMainView();
			updateInterfaceView();

		}
	}

	window->Wait();
}


void Game::updateCharacters() {

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

}

void Game::updateMainView() {

	sf::Vector2f viewCenter = mainCharacter->GetPosition();

	if(mainCharacter->GetPosition().x <= window->GetDefaultView().GetHalfSize().x) {
		viewCenter.x = window->GetDefaultView().GetHalfSize().x;
	}

	if(mainCharacter->GetPosition().x >= (mapSprite.GetSize().x - window->GetDefaultView().GetHalfSize().x)) {
		viewCenter.x = (mapSprite.GetSize().x - window->GetDefaultView().GetHalfSize().x);
	}

	if(mainCharacter->GetPosition().y <= window->GetDefaultView().GetHalfSize().y) {
		viewCenter.y = window->GetDefaultView().GetHalfSize().y;
	}

	if(mainCharacter->GetPosition().y >= (mapSprite.GetSize().y - window->GetDefaultView().GetHalfSize().y)) {
		viewCenter.y = (mapSprite.GetSize().y - window->GetDefaultView().GetHalfSize().y);
	}

	window->GetDefaultView().SetCenter(viewCenter);

}

void Game::updateInterfaceView() {

	if (framerateClock.GetElapsedTime() >= framerateRefresh) {

		ostringstream text;

		text << (int) (1.f / window->GetFrameTime()) << " fps";

		framerate.SetText(text.str());
		framerate.SetSize(20);
		framerateClock.Reset();

	}

	if (latencyClock.GetElapsedTime() >= latencyRefresh) {

		ostringstream text;

		text << (int) (connection->getLatency()) << " ms";

		latency.SetText(text.str());
		latency.SetSize(20);
		latencyClock.Reset();

	}

}

void Game::setIsFrameratePrinted(bool print, sf::Vector2f position, float refresh) {

	framerate.SetPosition(position);
	isFrameratePrinted 	= print;
	framerateRefresh 	= refresh;

}

void Game::setIsLatencyPrinted(bool print, sf::Vector2f position, float refresh) {

	latency.SetPosition(position);
	isLatencyPrinted 	= print;
	latencyRefresh 	= refresh;

}

void Game::init_static() {
	mapImage.LoadFromFile("build/client/resources/map.png");

}

sf::Sprite & Game::getMap() {
	return mapSprite;
}
