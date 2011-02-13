/* 
 * File:   EventHandler.h
 * Author: zapo
 *
 * Created on 12 janvier 2011, 10:04
 */

#ifndef EVENTHANDLER_H
#define	EVENTHANDLER_H

#include <SFML/Graphics.hpp>

class Window;

class EventHandler {

public:

	EventHandler();
	EventHandler(const EventHandler& orig);
	virtual ~EventHandler();
	virtual void handle(const sf::Event &event) const = 0 ;
	const Window& getHandledWindow() const;
	void setHandledWindow(Window&);

protected:

	Window * handledWindow;

};

#endif	/* EVENTHANDLER_H */

