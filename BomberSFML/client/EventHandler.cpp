/* 
 * File:   EventHandler.cpp
 * Author: zapo
 * 
 * Created on 12 janvier 2011, 10:04
 */

#include "EventHandler.h"
#include "Game.h"

EventHandler::EventHandler() {
	game = NULL;
}

EventHandler::EventHandler(const EventHandler& orig) {
}

EventHandler::~EventHandler() {
}

Game& EventHandler::getGame() const {
	return *game;
}

void EventHandler::setGame(Game& game) {
	this->game = &game;
}

bool EventHandler::canHandle(sf::Event::EventType type) {

	return (std::find(eventTypes.begin(), eventTypes.end(), type) != eventTypes.end());

}

