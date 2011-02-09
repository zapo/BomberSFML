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
#include "Connection.h"
#include "Character.h"
#include "Game.h"
#include "Window.h"
#include "ShootEventHandler.h"
#include <sstream>

/*
 * 
 */

sf::Image Character::tankImage;

int main(int argc, char** argv) {

	long id = 54;
	sf::IPAddress host = sf::IPAddress::LocalHost;

	ostringstream title;
	title << "BombrerSFML with id " << id;

	Window *window = new Window(800, 600, 32, title.str());

	Connection *connection = new Connection(7000, host, id);

	Game *game = new Game(*window, *connection);

	game->loadRessources();

	Character *me = new Character(id);

	game->addCharacter(id, *me);
	game->setMainCharacter(*me);

	window->addEventHandler(new ClosingEventHandler());
	window->addEventHandler(new MoveEventHandler(*me, *connection));
	window->addEventHandler(new ShootEventHandler(*me, *connection));

	window->setPrintFramerate(true, 1);

	game->run();
	delete game;

	return EXIT_SUCCESS;
}
