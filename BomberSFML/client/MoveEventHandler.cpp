/*
 * MoveRectEventHandler.cpp
 *
 *  Created on: 2011-01-13
 *      Author: zapo
 */

#include "MoveEventHandler.h"
#include "Game.h"
#include "Character.h"
#include "Connection.h"
#include "Window.h"
#include <iostream>

MoveEventHandler::MoveEventHandler() :
	EventHandler() {
}

MoveEventHandler::~MoveEventHandler() {
	// TODO Auto-generated destructor stub
}

void MoveEventHandler::handle(const sf::Event &event) {

	Window& window = game->getWindow();
	Connection& connection = game->getConnection();
	Character& character = game->getMainCharacter();

	if (event.Type == sf::Event::KeyPressed || event.Type
			== sf::Event::KeyReleased) {

		switch (event.Key.Code) {

		case sf::Key::Right:
		case sf::Key::Left:
		case sf::Key::Up:
		case sf::Key::Down:

		{
			if (event.Type == sf::Event::KeyPressed) {

				float left = character.GetPosition().x;
				float top = character.GetPosition().y;

				float oldLeft = left;
				float oldTop = top;

				bool rightHit = false, leftHit = false, upHit = false, downHit =
						false;

				float frametime = window.GetFrameTime();

				if (window.GetInput().IsKeyDown(sf::Key::Right)) {
					left += (speed * frametime);
					character.setOrientation(Character::RIGHT);
					rightHit = true;

				}

				if (window.GetInput().IsKeyDown(sf::Key::Left)) {
					left -= (speed * frametime);
					character.setOrientation(Character::LEFT);
					leftHit = true;
				}

				if (window.GetInput().IsKeyDown(sf::Key::Up)) {
					top -= (speed * frametime);
					character.setOrientation(Character::UP);
					upHit = true;
				}

				if (window.GetInput().IsKeyDown(sf::Key::Down)) {
					top += (speed * frametime);
					character.setOrientation(Character::DOWN);
					downHit = true;
				}

				if (downHit && leftHit)
					character.setOrientation(Character::LEFTDOWN);
				if (downHit && rightHit)
					character.setOrientation(Character::RIGHTDOWN);
				if (upHit && leftHit)
					character.setOrientation(Character::LEFTUP);
				if (upHit && rightHit)
					character.setOrientation(Character::RIGHTUP);

				if (oldLeft != left || oldTop != top) {


					Character temp;
					temp = character;

					temp.move(sf::Vector2f(left, top));

					connection.connectionMutex.Lock();

					bool setted = connection.setPosition(temp);

					connection.connectionMutex.Unlock();

				}

			} else {

				bool noMove = true;
				noMove = noMove && (!window.GetInput().IsKeyDown(
						sf::Key::Right));
				noMove = noMove && (!window.GetInput().IsKeyDown(
						sf::Key::Left));
				noMove = noMove && (!window.GetInput().IsKeyDown(
						sf::Key::Up));
				noMove = noMove && (!window.GetInput().IsKeyDown(
						sf::Key::Down));

				if (noMove) {

					window.drawableObjectsMutex.Lock();
					character.setCurrentAction(Character::IDLEING);
					window.drawableObjectsMutex.Unlock();

					connection.connectionMutex.Lock();

					connection.setPosition(character);

					connection.connectionMutex.Unlock();

				}

			}

			break;

		}
		}

	}

}
