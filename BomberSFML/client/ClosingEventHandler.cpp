/* 
 * File:   ClosingEventHandler.cpp
 * Author: zapo
 * 
 * Created on 12 janvier 2011, 15:30
 */

#include "ClosingEventHandler.h"
#include "Game.h"
#include "Window.h"
#include <SFML/Graphics.hpp>

using namespace std;

ClosingEventHandler::ClosingEventHandler() {
	eventTypes.push_back(sf::Event::KeyPressed);
	eventTypes.push_back(sf::Event::Closed);
}

ClosingEventHandler::ClosingEventHandler(const ClosingEventHandler & orig) {
}

ClosingEventHandler::~ClosingEventHandler() {
}

void ClosingEventHandler::handle(const sf::Event & event) {

	if (event.Type == sf::Event::Closed) {
		this->game->getWindow().Close();
	}

	if (event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Q) {
		this->game->getWindow().Close();
	}

}

