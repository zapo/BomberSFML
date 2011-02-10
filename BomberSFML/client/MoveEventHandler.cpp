/*
 * MoveRectEventHandler.cpp
 *
 *  Created on: 2011-01-13
 *      Author: zapo
 */

#include "MoveEventHandler.h"
#include "Connection.h"
#include "Window.h"
#include "Character.h"
#include <iostream>

MoveEventHandler::MoveEventHandler(Character &shape, Connection &connection) :
	EventHandler(), shape(&shape), connection(&connection) {
}

MoveEventHandler::~MoveEventHandler() {
	// TODO Auto-generated destructor stub
}

void MoveEventHandler::handle(sf::Event &event) {

	if (event.Type == sf::Event::KeyPressed || event.Type
			== sf::Event::KeyReleased) {

		switch (event.Key.Code) {

		case sf::Key::Right:
		case sf::Key::Left:
		case sf::Key::Up:
		case sf::Key::Down:

		{
			if (event.Type == sf::Event::KeyPressed) {

				float left = shape->GetPosition().x;
				float top = shape->GetPosition().y;

				float oldLeft = left;
				float oldTop = top;

				bool rightHit = false, leftHit = false, upHit = false, downHit =
						false;

				float frametime = handledWindow->GetFrameTime();

				if (handledWindow->GetInput().IsKeyDown(sf::Key::Right)) {
					left += (speed * frametime);
					shape->setOrientation(Character::RIGHT);
					rightHit = true;

				}

				if (handledWindow->GetInput().IsKeyDown(sf::Key::Left)) {
					left -= (speed * frametime);
					shape->setOrientation(Character::LEFT);
					leftHit = true;
				}

				if (handledWindow->GetInput().IsKeyDown(sf::Key::Up)) {
					top -= (speed * frametime);
					shape->setOrientation(Character::UP);
					upHit = true;
				}

				if (handledWindow->GetInput().IsKeyDown(sf::Key::Down)) {
					top += (speed * frametime);
					shape->setOrientation(Character::DOWN);
					downHit = true;
				}

				if (downHit && leftHit)
					shape->setOrientation(Character::LEFTDOWN);
				if (downHit && rightHit)
					shape->setOrientation(Character::RIGHTDOWN);
				if (upHit && leftHit)
					shape->setOrientation(Character::LEFTUP);
				if (upHit && rightHit)
					shape->setOrientation(Character::RIGHTUP);

				if (oldLeft != left || oldTop != top) {


					Character temp;
					temp = *shape;

					temp.move(sf::Vector2f(left, top));

					connection->connectionMutex.Lock();

					bool setted = connection->setPosition(temp);

					connection->connectionMutex.Unlock();

				}

			} else {

				bool noMove = true;
				noMove = noMove && (!handledWindow->GetInput().IsKeyDown(
						sf::Key::Right));
				noMove = noMove && (!handledWindow->GetInput().IsKeyDown(
						sf::Key::Left));
				noMove = noMove && (!handledWindow->GetInput().IsKeyDown(
						sf::Key::Up));
				noMove = noMove && (!handledWindow->GetInput().IsKeyDown(
						sf::Key::Down));

				if (noMove) {

					handledWindow->drawableObjectsMutex.Lock();
					shape->setCurrentAction(Character::IDLEING);
					handledWindow->drawableObjectsMutex.Unlock();

					connection->connectionMutex.Lock();

					connection->setPosition(*shape);

					connection->connectionMutex.Unlock();

				}

			}

			break;

		}
		}

	}

}
