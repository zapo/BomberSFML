/* 
 * File:   Window.h
 * Author: zapo
 *
 * Created on 12 janvier 2011, 09:27
 */

#ifndef WINDOW_H
#define	WINDOW_H

#include "EventHandler.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <map>


using namespace std;

namespace BMSfml {

    class Window {
        
    public:
        Window(int,int,int,string);
        Window(const Window& orig);
        virtual ~Window();

        void addEvent(sf::Event&, EventHandler&);

        void run();

        map<sf::Event, EventHandler&> getEventHandlers();
    private:

        string title;
        int width;
        int height;
        int colors;

        sf::RenderWindow *sfWindow;

        map<sf::Event, EventHandler&> eventHandlers;

    };

}

#endif	/* WINDOW_H */

