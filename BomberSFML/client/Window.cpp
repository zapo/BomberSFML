/* 
 * File:   Window.cpp
 * Author: zapo
 * 
 * Created on 12 janvier 2011, 09:27
 */

#include <list>
#include "Window.h"
#include "EventHandler.h"
#include <iostream>
#include <sstream>

using namespace std;

Window::Window(const int width, const int height, const int colors, const string title) :

	sf::RenderWindow(sf::VideoMode(width, height, colors), title),
			sf::Thread(),
			title(title) {


	this->SetActive(false);

}

Window::Window(const Window& orig) {
}

Window::~Window() {
}

void Window::Run() {

	while (this->IsOpened()) {

		sf::Event event;

		while (this->GetEvent(event)) {

			eventHandlersMutex.Lock();

			for (iho = eventHandlers.begin(); iho != eventHandlers.end(); iho++) {

				EventHandler *eh = *(iho);

				if (eh != NULL && eh->canHandle(event.Type)){
					eh->handle(event);
				}
			}

			eventHandlersMutex.Unlock();

		}

		this->Clear();

		drawableObjectsMutex.Lock();

		for (ido = drawableObjects.begin(); ido != drawableObjects.end(); ido++) {

			this->SetView(*(ido->first));

			for(idoo = ido->second.begin(); idoo != ido->second.end(); idoo++) {

				for(idooo = idoo->second.begin(); idooo != idoo->second.end(); idooo++) {

					const sf::Drawable * dro = *(idooo);

					if (dro != NULL) {
						this->Draw(*dro);
					}
				}
			}
		}

		drawableObjectsMutex.Unlock();

		this->Display();
	}

}



void Window::addEventHandler(EventHandler &handler) {

	eventHandlersMutex.Lock();

	this->eventHandlers.push_back(&handler);

	eventHandlersMutex.Unlock();
}

list<EventHandler*> Window::getEventHandlers() const {

	return this->eventHandlers;

}

void Window::removeDrawableObject(sf::Drawable& object, sf::View& view, unsigned int layer, bool free) {

	drawableObjectsMutex.Lock();

	if(drawableObjects.find(&view) != drawableObjects.end()) {

		if(drawableObjects[&view].find(layer) != drawableObjects[&view].end()) {

			drawableObjects[&view][layer].remove(&object);
		}

	}

	if (free) {
		delete &object;
	}

	drawableObjectsMutex.Unlock();
}

void Window::addDrawableObject(const sf::Drawable& object, sf::View& view, unsigned int layer) {

	drawableObjectsMutex.Lock();

	this->drawableObjects[&view][layer].push_back(&object);

	drawableObjectsMutex.Unlock();
}
map<sf::View* ,map<unsigned int, list<const sf::Drawable*> > > Window::getDrawableObjects() const {

	return drawableObjects;

}

