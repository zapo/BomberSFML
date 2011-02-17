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
			mainLayer(Layer(GetDefaultView())),
			interfaceLayer(Layer(GetInterfaceView())),
			title(title) {

	interface.SetCenter		(sf::Vector2f(width/2, height/2));
	interface.SetHalfSize	(sf::Vector2f(width/2, height/2));

	this->SetActive(false);
	addLayer(mainLayer);
	addLayer(interfaceLayer);
}

Window::Window(const Window& orig) :
		mainLayer(orig.mainLayer),
		interfaceLayer(orig.interfaceLayer),
		layers(orig.layers) {
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

		for (lit = layers.begin(); lit != layers.end(); lit++) {

			Layer & layer = **lit;
			this->SetView(layer.getView());

			vector<sf::Drawable*> & objects = layer.getObjects();
			vector<sf::Drawable*>::iterator objit;

			for(objit = objects.begin(); objit != objects.end(); objit++) {

				const sf::Drawable * dro = *(objit);
				if(dro != NULL) {
					this->Draw(*dro);
				}
			}
		}

		drawableObjectsMutex.Unlock();

		this->Display();
	}

}

void Window::addLayer(Layer & layer) {

	drawableObjectsMutex.Lock();
	layers.push_back(&layer);
	drawableObjectsMutex.Unlock();
}


void Window::addEventHandler(EventHandler &handler) {

	eventHandlersMutex.Lock();

	this->eventHandlers.push_back(&handler);

	eventHandlersMutex.Unlock();
}

list<EventHandler*> Window::getEventHandlers() const {

	return this->eventHandlers;

}

sf::View& Window::GetInterfaceView() {
	return interface;
}

Layer & Window::GetMainLayer() {

	return mainLayer;

}
Layer & Window::GetInterfaceLayer() {

	return interfaceLayer;

}



