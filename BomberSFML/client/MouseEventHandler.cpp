/*
 * MouseEventHandler.cpp
 *
 *  Created on: 2011-02-10
 *      Author: zapo
 */

#include "MouseEventHandler.h"
#include "Window.h"
#include "Game.h"
#include <iostream>

MouseEventHandler::MouseEventHandler() {
	eventTypes.push_back(sf::Event::MouseWheelMoved);
}

MouseEventHandler::~MouseEventHandler() {
	// TODO Auto-generated destructor stub
}

void MouseEventHandler::handle(const sf::Event &event) {

	Window &window = game->getWindow();

	if(event.Type == sf::Event::MouseWheelMoved) {

		sf::Vector2f halfSize = window.GetDefaultView().GetHalfSize() ;

		float factor = 95.f/100.f;

		if(event.MouseWheel.Delta < 0) {
			factor = 1/factor;
		}

		halfSize.x *= factor;
		halfSize.y *= factor;


		if(halfSize.x > game->getMap().GetSize().x / 2 || halfSize.y > game->getMap().GetSize().y / 2) {

			halfSize.x = game->getMap().GetSize().x / 2;
			halfSize.y = game->getMap().GetSize().y / 2;

		}

		window.GetDefaultView().SetHalfSize(halfSize);

	}

}
