/*
 * MoveRectEventHandler.h
 *
 *  Created on: 2011-01-13
 *      Author: zapo
 */

#ifndef MOVERECTEVENTHANDLER_H_
#define MOVERECTEVENTHANDLER_H_

#include "EventHandler.h"
#include <SFML/Graphics.hpp>

class MoveRectEventHandler : EventHandler {
public:
	MoveRectEventHandler(sf::Drawable*);
	virtual ~MoveRectEventHandler();
	void handle(sf::Event &event);

private:
	sf::Drawable* shape;
};

#endif /* MOVERECTEVENTHANDLER_H_ */
