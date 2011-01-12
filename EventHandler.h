/* 
 * File:   EventHandler.h
 * Author: zapo
 *
 * Created on 12 janvier 2011, 10:04
 */

#ifndef EVENTHANDLER_H
#define	EVENTHANDLER_H

#include <SFML/Graphics.hpp>

namespace BMSfml {

    class EventHandler {

    public:
        EventHandler();
        EventHandler(const EventHandler& orig);
        virtual ~EventHandler();
        virtual void handle(sf::Event &event) = 0;
    private:

    };

}

#endif	/* EVENTHANDLER_H */

