/* 
 * File:   ClosingEventHandler.cpp
 * Author: zapo
 * 
 * Created on 12 janvier 2011, 15:30
 */

#include "ClosingEventHandler.h"
#include <iostream>
#include <SFML/Window/Event.hpp>

using namespace BMSfml;
using namespace std;

ClosingEventHandler::ClosingEventHandler() {
}

ClosingEventHandler::ClosingEventHandler(const ClosingEventHandler& orig) {
}

ClosingEventHandler::~ClosingEventHandler() {
}

void ClosingEventHandler::handle(sf::Event &event) {

    cout << event.Type << endl;

}

