/*
 * Connection.cpp
 *
 *  Created on: 2011-01-17
 *      Author: zapo
 */

#include "Connection.h"
#include "Window.h"
#include "Application.h"
#include "MoveRectEventHandler.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

Connection::Connection(sf::SocketTCP& sock, unsigned int port,
		sf::IPAddress const& address) :
	host(address), port(port), socket(sock), sf::Thread() {
}

Connection::~Connection() {
	// TODO Auto-generated destructor stub
}

bool Connection::connect() {

	cout << "Trying to connect to server..." << endl;
	return socket.Connect(port, host) == sf::Socket::Done;
}

bool Connection::isConnected() {

	return socket.IsValid();
}

void Connection::Run() {

	if (!connect() || !isConnected()) {
		cout << "Cant contect ..." << endl;
		return;
	}

	cout << "Got a valid socket connected to '" << host << "' !" << endl;



	sf::Packet received;

	if (socket.Receive(received) == sf::Socket::Done) {

		sf::Uint16 x, y;

		received >> x >> y;

		Window *win = Application::getInstance()->getWindow();

		sf::Color fillColor = sf::Color(128, 128, 128);

		sf::Shape *rect = new sf::Shape();

		rect->AddPoint(x, y, fillColor);
		rect->AddPoint(x, y + 10, fillColor);
		rect->AddPoint(x + 10, y + 10, fillColor);
		rect->AddPoint(x + 10, y, fillColor);

		win->addDrawableObject((sf::Drawable*) rect);

		MoveRectEventHandler *moveHandler = new MoveRectEventHandler(rect);
		win->addEventHandler((EventHandler*) moveHandler);

	}


}

