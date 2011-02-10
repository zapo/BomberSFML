/*
 * MouseEventHandler.cpp
 *
 *  Created on: 2011-02-10
 *      Author: zapo
 */

#include "MouseEventHandler.h"
#include "Window.h"

MouseEventHandler::MouseEventHandler() {
	// TODO Auto-generated constructor stub

}

MouseEventHandler::~MouseEventHandler() {
	// TODO Auto-generated destructor stub
}

void MouseEventHandler::handle(sf::Event &event) {

	if(event.Type == sf::Event::MouseWheelMoved) {

		sf::Vector2f halfSize = handledWindow->GetDefaultView().GetHalfSize() ;

		halfSize.x += event.MouseWheel.Delta * 4;
		halfSize.y += event.MouseWheel.Delta * 4;

		handledWindow->GetDefaultView().SetHalfSize(halfSize);

	}

}
