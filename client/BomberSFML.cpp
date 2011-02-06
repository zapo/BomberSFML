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

/*
 * 
 */

sf::Image Character::tankImage;

int main(int argc, char** argv) {


	long id = 41;

	Window *window = new Window(800, 600, 32, "BombrerSFML");
	Connection *connection = new Connection(new sf::SocketTCP, 8889, sf::IPAddress::LocalHost, id);

	Game *game = new Game(*window, *connection);

	game->loadRessources();

	Character *me = new Character(id);

	game->addCharacter(id, *me);
	game->setMainCharacter(*me);

	window->addEventHandler(new ClosingEventHandler());
	window->addEventHandler(new MoveEventHandler(*me, *connection));
	window->addEventHandler(new ShootEventHandler(*me));


	if(!connection->connect()) {

		std::cout << "A problem occurred while connecting to host, terminating..." << std::endl;
		std::cout.flush();

		delete game;
		exit(2);

	}

	window->Launch();
	game->Launch();


	window->Wait();
	game->Terminate();

	delete game;

	return EXIT_SUCCESS;
}
