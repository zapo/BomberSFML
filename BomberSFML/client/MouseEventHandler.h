/*
 * MouseEventHandler.h
 *
 *  Created on: 2011-02-10
 *      Author: zapo
 */

#ifndef MOUSEEVENTHANDLER_H_
#define MOUSEEVENTHANDLER_H_

#include "EventHandler.h"

class MouseEventHandler: public EventHandler {
public:
	MouseEventHandler();
	virtual ~MouseEventHandler();
	void handle(const sf::Event &event);
};

#endif /* MOUSEEVENTHANDLER_H_ */
