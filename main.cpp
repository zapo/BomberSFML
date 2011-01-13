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
#include <SFML/Network.hpp>


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


	sf::SocketTCP sock;
	unsigned short port = 8888;

	if (sock.Connect(port, sf::IPAddress::LocalHost, 20.) == sf::Socket::Done) {

		char message[128] = "Yo server";

		sock.Send(message, sizeof(message));

	}





	window.run();



	return EXIT_SUCCESS;
}
