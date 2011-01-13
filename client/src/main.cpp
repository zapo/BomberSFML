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
	unsigned short port = 8889;

	if (sock.Connect(port, sf::IPAddress::LocalHost) != sf::Socket::Done) {
		cout << "Can't connect" << endl;
		return 1;
	}

	bool connected = true;

	while(connected) {

		sf::Packet packet;

		std::string Message;
		std::cout << "Say something to the server : ";
		std::getline(std::cin, Message);

		packet << Message;

		connected = (sock.Send(packet) == sf::Socket::Done);

		sf::Packet received;

		connected = (sock.Receive(received) == sf::Socket::Done);

		received >> Message;

		cout << Message << endl;

	}


	sock.Close();

	//window.run();


	return EXIT_SUCCESS;
}
