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
			title(title),
			isFrameratePrinted(false),
			framerateRefresh(1) {


	this->SetActive(false);
	interface.SetCenter(sf::Vector2f(width/2, height/2));
	interface.SetHalfSize(sf::Vector2f(width/2, height/2));
}

Window::Window(const Window& orig) {
}

Window::~Window() {

	this->removeDrawableObject(framerate, 999, false);

	list<const sf::Drawable*>::iterator idoo;

	for (ido = drawableObjects.begin(); ido != drawableObjects.end(); ido++) {

		ido->second.clear();
	}
	drawableObjects.clear();

	/*for (iho = eventHandlers.begin(); iho != eventHandlers.end(); iho++) {
		if (*iho != NULL) {
			delete *iho;
		}
	}*/
	eventHandlers.clear();

}

void Window::Run() {

	framerateClock.Reset();

	while (this->IsOpened()) {

		sf::Event event;

		while (this->GetEvent(event)) {

			eventHandlersMutex.Lock();

			for (iho = eventHandlers.begin(); iho != eventHandlers.end(); iho++) {

				EventHandler *eh = *(iho);

				if (eh != NULL) {
					eh->handle(event);
				}
			}

			eventHandlersMutex.Unlock();

		}

		this->Clear();

		this->SetView(this->GetDefaultView());

		drawableObjectsMutex.Lock();

		list<const sf::Drawable*>::iterator idoo;

		for (ido = drawableObjects.begin(); ido != drawableObjects.end(); ido++) {

			for(idoo = ido->second.begin(); idoo != ido->second.end(); idoo++) {

				const sf::Drawable *dro = *(idoo);

				if (dro != NULL) {
					this->Draw(*dro);
				}
			}
		}

		drawableObjectsMutex.Unlock();

		this->SetView(interface);

		if(isFrameratePrinted) {
			updateFramerate();
			this->Draw(framerate);
		}

		this->Display();
	}

}

void Window::updateFramerate() {

	if (framerateClock.GetElapsedTime() >= framerateRefresh) {

		ostringstream text;

		text << (int) (1.f / GetFrameTime()) << " fps";

		framerate.SetText(text.str());
		framerate.SetSize(20);

		framerateClock.Reset();

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

void Window::removeDrawableObject(sf::Drawable& object, unsigned int layer, bool free) {

	drawableObjectsMutex.Lock();

	if(drawableObjects.find(layer) != drawableObjects.end()) {

		drawableObjects[layer].remove(&object);

	}

	if (free) {
		delete &object;
	}

	drawableObjectsMutex.Unlock();
}

void Window::addDrawableObject(const sf::Drawable& object, unsigned int layer) {

	drawableObjectsMutex.Lock();

	this->drawableObjects[layer].push_back(&object);

	drawableObjectsMutex.Unlock();
}
map<unsigned int, list<const sf::Drawable*> > Window::getDrawableObjects() const {

	return drawableObjects;

}

void Window::setIsFrameratePrinted(bool print, sf::Vector2f position, float refresh) {

	framerate.SetPosition(position);
	isFrameratePrinted = print;
	framerateRefresh = refresh;

}

