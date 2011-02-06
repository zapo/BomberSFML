/*
 * MoveRectEventHandler.h
 *
 *  Created on: 2011-01-13
 *      Author: zapo
 */

#ifndef MOVERECTEVENTHANDLER_H_
#define MOVEEVENTHANDLER_H_

#include "EventHandler.h"

#include <SFML/Graphics.hpp>

class Connection;
class Window;
class Character;

class MoveEventHandler : public EventHandler {
public:
	MoveEventHandler(Character&, Connection &connection);
	virtual ~MoveEventHandler();
	void handle(sf::Event &event);

private:
	Character* shape;
	Connection *connection;
	static const float speed = 2;
	Window *window;
};

#endif /* MOVEEVENTHANDLER_H_ */
