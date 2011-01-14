/*
 * MoveRectEventHandler.cpp
 *
 *  Created on: 2011-01-13
 *      Author: zapo
 */

#include "MoveRectEventHandler.h"
#include "Window.h"
#include <iostream>

MoveRectEventHandler::MoveRectEventHandler(sf::Drawable* shape) : EventHandler(), shape(shape) {}

MoveRectEventHandler::~MoveRectEventHandler() {
	// TODO Auto-generated destructor stub
}

void MoveRectEventHandler::handle(sf::Event &event) {

	if(event.Type == sf::Event::KeyPressed) {

		float left = shape->GetPosition().x;
		float top = shape->GetPosition().y;

		//float frametime = this->handledWindow->GetFrameTime();


		if(handledWindow->GetInput().IsKeyDown(sf::Key::Right)){
			left += 10;
		}

		if(handledWindow->GetInput().IsKeyDown(sf::Key::Left)){
			left -= 10;
		}

		if(handledWindow->GetInput().IsKeyDown(sf::Key::Up)){
			top -= 10;
		}

		if(handledWindow->GetInput().IsKeyDown(sf::Key::Down)){
			top += 10;
		}

		shape->SetPosition(left, top);


	}

}
