/* 
 * File:   Window.cpp
 * Author: zapo
 * 
 * Created on 12 janvier 2011, 09:27
 */

#include "Window.h"
#include <vector>
#include "EventHandler.h"

using namespace std;


Window::Window(int width, int height, int colors, string title) :

		sf::RenderWindow(sf::VideoMode(width, height, colors), title),
		title(title),
		width(width),
		height(height),
		colors(colors)

{}

Window::Window(const Window& orig) {
}

Window::~Window() {
}

void Window::run() {

	// Start game loop
	while (this->IsOpened())
	{
		// Process events
		sf::Event event;
		while (this->GetEvent(event))
		{
			for(unsigned int i = 0; i < this->getEventHandlers().size(); i++) {

				EventHandler *eh = this->getEventHandlers()[i];

				if(eh != NULL) {
					eh->handle(event);
				}
			}
		}

		// Clear the screen (fill it with black color)
		this->Clear();

		// Display window contents on screen
		this->Display();
	}

}

void Window::addEventHandler(EventHandler *handler) {

	if(handler != NULL) {
		this->eventHandlers.push_back(handler);
		handler->setHandledWindow(this);
	}

}

 vector<EventHandler*> Window::getEventHandlers() {

	return this->eventHandlers;

}





