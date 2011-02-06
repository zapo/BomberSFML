/*
 * ShootEventHandler.h
 *
 *  Created on: 2011-02-02
 *      Author: zapo
 */

#ifndef SHOOTEVENTHANDLER_H_
#define SHOOTEVENTHANDLER_H_

#include "EventHandler.h"

class Character;

class ShootEventHandler: public EventHandler {
public:
	ShootEventHandler(Character &);
	virtual ~ShootEventHandler();
	void handle(sf::Event &event);

private:
	Character* handledCharacter;
};

#endif /* SHOOTEVENTHANDLER_H_ */
