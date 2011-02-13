/* 
 * File:   EventHandler.cpp
 * Author: zapo
 * 
 * Created on 12 janvier 2011, 10:04
 */

#include "EventHandler.h"
#include "Window.h"

EventHandler::EventHandler() {
	handledWindow = NULL;
}

EventHandler::EventHandler(const EventHandler& orig) {
}

EventHandler::~EventHandler() {
}

const Window& EventHandler::getHandledWindow() const {
	return *handledWindow;
}

void EventHandler::setHandledWindow(Window& window) {
	handledWindow = &window;
}

