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
class Connection;

class ShootEventHandler: public EventHandler {
public:
	ShootEventHandler();
	virtual ~ShootEventHandler();
	void handle(const sf::Event &event) const;

private:
};

#endif /* SHOOTEVENTHANDLER_H_ */
