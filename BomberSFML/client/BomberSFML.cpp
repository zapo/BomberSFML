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

#define __USERID				19


int main(int argc, char ** argv) {

	long id = __USERID;
	sf::IPAddress host = sf::IPAddress::LocalHost;

	ostringstream title;
	title << "BombrerSFML with id " << id;

	Window window(__SCREEN_WIDH, __SCREEN_HEIGHT, __COLOR, title.str());

	Connection connection(7000, host, id);

	Game game(window, connection);

	game.loadRessources();

	Character me(id);
	game.setMainCharacter(me);

	ClosingEventHandler ceh;
	MouseEventHandler 	meh;
	MoveEventHandler 	moeh;
	ShootEventHandler 	seh;

	game.addEventHandler(ceh);
	game.addEventHandler(meh);
	game.addEventHandler(moeh);
	game.addEventHandler(seh);

	game.setIsFrameratePrinted(true, sf::Vector2f(__SCREEN_WIDH - 100, 40), 0.08);
	game.setIsLatencyPrinted(true, sf::Vector2f(__SCREEN_WIDH - 100, 60), 0.08);
	game.run();

	return EXIT_SUCCESS;
}
