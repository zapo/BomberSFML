/* 
 * File:   EventHandler.h
 * Author: zapo
 *
 * Created on 12 janvier 2011, 10:04
 */

#ifndef EVENTHANDLER_H
#define	EVENTHANDLER_H

#include <SFML/Graphics.hpp>
#include <list>

class Game;

class EventHandler {

public:

	EventHandler();
	EventHandler(const EventHandler& orig);
	virtual ~EventHandler();
	virtual void handle(const sf::Event &event) = 0 ;
	bool canHandle(sf::Event::EventType type);
	Game& getGame() const;
	void setGame(Game&);

protected:

	std::list<sf::Event::EventType> eventTypes;
	Game * game;

};

#endif	/* EVENTHANDLER_H */

