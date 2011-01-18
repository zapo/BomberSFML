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
#include "Application.h"
#include "Connection.h"


using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

	Application* app = Application::getInstance();

	sf::SocketTCP sock;
	unsigned short port = 8889;

	ClosingEventHandler closeHandler;

	Connection *connection = new Connection(sock, port, sf::IPAddress::LocalHost);

	app->setConnection(connection);


	Window window(800, 600, 32, "Test Window");

	app->setWindow(&window);



	window.addEventHandler((EventHandler*) &closeHandler);




	window.run();

	delete app;


	return EXIT_SUCCESS;
}
