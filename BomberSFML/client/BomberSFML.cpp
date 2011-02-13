/* 
 * File:   main.cpp
 * Author: zapo
 *
 * Created on 11 janvier 2011, 12:45
 */

#include <cstdlib>
#include <iostream>
#include "ClosingEventHandler.h"
#include "MoveEventHandler.h"
#include "MouseEventHandler.h"
#include "Connection.h"
#include "Character.h"
#include "Game.h"
#include "Window.h"
#include "ShootEventHandler.h"
#include <sstream>

#define __SCREEN_WIDH 			1024
#define __SCREEN_HEIGHT 		768
#define __COLOR 				32

#define __USERID				2

/*
 * 
 */

int main(int argc, char** argv) {

	long id = __USERID;
	sf::IPAddress host = sf::IPAddress::LocalHost;

	ostringstream title;
	title << "BombrerSFML with id " << id;

	Window *window = new Window(__SCREEN_WIDH, __SCREEN_HEIGHT, __COLOR, title.str());

	Connection *connection = new Connection(7000, host, id);

	Game *game = new Game(*window, *connection);

	game->loadRessources();

	Character *me = new Character(id);

	game->addCharacter(id, *me);
	game->setMainCharacter(*me);

	window->addEventHandler(*(new ClosingEventHandler()));
	window->addEventHandler(*(new MoveEventHandler(*me, *connection)));
	window->addEventHandler(*(new ShootEventHandler(*me, *connection)));
	window->addEventHandler(*(new MouseEventHandler()));

	window->setIsFrameratePrinted(true, sf::Vector2f(__SCREEN_WIDH - 100, 40), 0.06);

	game->run();
	delete game;

	return EXIT_SUCCESS;
}
