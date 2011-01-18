/* 
 * File:   Window.cpp
 * Author: zapo
 * 
 * Created on 12 janvier 2011, 09:27
 */

#include "Window.h"
#include <vector>
#include "EventHandler.h"
#include <iostream>

using namespace std;


Window::Window(int width, int height, int colors, string title) :

		sf::RenderWindow(sf::VideoMode(width, height, colors), title),
		title(title)

{}

Window::Window(const Window& orig) {
}

Window::~Window() {
}

void Window::run() {

	// Start game loop
	while (this->IsOpened()) {
		// Process events
		sf::Event event;


		while (this->GetEvent(event)) {

			eventHandlersMutex.Lock();

			for(iho = eventHandlers.begin(); iho != eventHandlers.end(); iho++) {

				EventHandler *eh = *(iho);

				if(eh != NULL) {
					eh->handle(event);
				}
			}

			eventHandlersMutex.Unlock();

		}

		// Clear the screen (fill it with black color)
		this->Clear();

		drawableObjectsMutex.Lock();

		for(ido = drawableObjects.begin(); ido != drawableObjects.end(); ido++) {

			sf::Drawable *dro = *(ido);

			if(dro != NULL) {
				this->Draw(*dro);
			}
		}

		drawableObjectsMutex.Unlock();


		// Display window contents on screen
		this->Display();
	}

}

void Window::addEventHandler(EventHandler *handler) {

	eventHandlersMutex.Lock();

	if(handler != NULL) {

		this->eventHandlers.push_back(handler);

		handler->setHandledWindow(this);

	}

	eventHandlersMutex.Unlock();

}

 vector<EventHandler*> Window::getEventHandlers() {

	return this->eventHandlers;

}


void Window::addDrawableObject(sf::Drawable* object) {

	drawableObjectsMutex.Lock();

	this->drawableObjects.push_back(object);

	drawableObjectsMutex.Unlock();
}
vector<sf::Drawable*> Window::getDrawableObjects() {

	return this->drawableObjects;

}





