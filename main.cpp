/* 
 * File:   main.cpp
 * Author: zapo
 *
 * Created on 11 janvier 2011, 12:45
 */


#include <cstdlib>
#include <iostream>
#include "Window.h"
#include "ClosingEventHandler.h"

using namespace std;
using namespace BMSfml;

/*
 * 
 */
int main(int argc, char** argv) {

    // Create the main rendering window
    Window window(800, 600, 32, "Test Window");

    ClosingEventHandler closeHandler;

    /*sf::Event::KeyEvent qEvent;
    qEvent.Code = sf::Key::Q;*/
    //window.addEvent((sf::Event)qEvent, (EventHandler)closeHandler);

    map<sf::Event, EventHandler&> eventHandlers = window.getEventHandlers();

    map<sf::Event, EventHandler&>::iterator it;

    for(it = eventHandlers.begin(); it != eventHandlers.end(); it++) {

        //cout << it->first << " => " << it->second << endl;

    }

    


    // Run the main window loop
    window.run();

    return EXIT_SUCCESS;
}
