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

Window::Window(int width, int height, int colors, string title) :

	sf::RenderWindow(sf::VideoMode(width, height, colors), title),
			sf::Thread(), title(title), printFramerate(false),
			framerateRefresh(1) {

	this->SetActive(false);
}

Window::Window(const Window& orig) {
}

Window::~Window() {

	drawableObjects.remove((sf::Drawable*) &framerate);

	for (ido = drawableObjects.begin(); ido != drawableObjects.end(); ido++) {

		if (*ido != NULL) {
			delete *ido;
		}
	}
	drawableObjects.clear();

	for (iho = eventHandlers.begin(); iho != eventHandlers.end(); iho++) {
		if (*iho != NULL) {
			delete *iho;
		}
	}
	eventHandlers.clear();

}

void Window::Run() {

	sf::Clock framerateClock;
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

		drawableObjectsMutex.Lock();

		for (ido = drawableObjects.begin(); ido != drawableObjects.end(); ido++) {

			sf::Drawable *dro = *(ido);

			if (dro != NULL) {
				this->Draw(*dro);
			}
		}

		drawableObjectsMutex.Unlock();

		if (printFramerate && framerateClock.GetElapsedTime()
				>= framerateRefresh) {

			ostringstream text;

			text << (int) (1.f / GetFrameTime()) << " fps";

			framerate.SetText(text.str());
			framerate.SetSize(20);
			framerate.SetPosition(sf::Vector2f((GetWidth() - 100), 20));

			framerateClock.Reset();

		}

		// Display window contents on screen
		this->Display();
	}

}

void Window::addEventHandler(EventHandler *handler) {

	eventHandlersMutex.Lock();

	if (handler != NULL) {

		this->eventHandlers.push_back(handler);

		handler->setHandledWindow(this);

	}

	eventHandlersMutex.Unlock();

}

list<EventHandler*> Window::getEventHandlers() {

	return this->eventHandlers;

}

void Window::removeDrawableObject(sf::Drawable* object, bool free) {

	drawableObjectsMutex.Lock();

	drawableObjects.remove(object);

	if (free) {
		delete object;
	}

	drawableObjectsMutex.Unlock();
}

void Window::addDrawableObject(sf::Drawable* object) {

	drawableObjectsMutex.Lock();

	this->drawableObjects.push_back(object);

	drawableObjectsMutex.Unlock();
}
list<sf::Drawable*> Window::getDrawableObjects() {

	return drawableObjects;

}

void Window::setPrintFramerate(bool print, float refresh) {

	if (print) {

		addDrawableObject(&framerate);

	} else {
		removeDrawableObject(&framerate, false);
	}

	printFramerate = print;
	framerateRefresh = refresh;

}

