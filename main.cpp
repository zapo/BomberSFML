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


using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

	Window window(800, 600, 32, "Test Window");

	ClosingEventHandler *closeHandler = new ClosingEventHandler();

	window.addEventHandler((EventHandler*) closeHandler);

	window.run();

	return EXIT_SUCCESS;
}
