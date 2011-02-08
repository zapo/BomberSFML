/* 
 * File:   ClosingEventHandler.h
 * Author: zapo
 *
 * Created on 12 janvier 2011, 15:30
 */

#ifndef CLOSINGEVENTHANDLER_H
#define	CLOSINGEVENTHANDLER_H

#include "EventHandler.h"

class ClosingEventHandler: public EventHandler {

public:

	ClosingEventHandler();
	ClosingEventHandler(const ClosingEventHandler& orig);
	virtual ~ClosingEventHandler();

	void handle(sf::Event &event);
private:

};

#endif	/* CLOSINGEVENTHANDLER_H */

