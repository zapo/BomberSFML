/* 
 * File:   main.cpp
 * Author: zapo
 *
 * Created on 11 janvier 2011, 12:45
 */

#include <cstdlib>
#include <iostream>
#include "Window.h"
#include "ClosingEventHandler.h"
#include "MoveRectEventHandler.h"


using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

	Window window(800, 600, 32, "Test Window");

	ClosingEventHandler closeHandler;


	window.addEventHandler((EventHandler*) &closeHandler);



	sf::Shape rect = sf::Shape::Rectangle(0, 0, 50, 50, sf::Color(255,255,255));

	window.addDrawableObject((sf::Drawable*)&rect);

	MoveRectEventHandler moveHandler(&rect);
	window.addEventHandler((EventHandler*) &moveHandler);


	window.run();



	return EXIT_SUCCESS;
}
