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
#include <iostream>
#define IS_ALIVE 1
#define ALIVE 2

using namespace std;

Connection::Connection(sf::SocketTCP& sock, unsigned int port, sf::IPAddress const& address) : host(address), port(port), socket(sock), sf::Thread() {

	this->Launch();

}

Connection::~Connection() {
	// TODO Auto-generated destructor stub
}

bool Connection::connect() {

	cout << "Trying to connect to " << host << endl;
	return socket.Connect(port, host) == sf::Socket::Done;
}

bool Connection::isConnected() {

	return socket.IsValid();
}



void Connection::Run() {

		if(!connect()) {
			cout << "Cant contect ..." << endl;
			return;
		}

		sf::Packet received;

		if(socket.Receive(received) == sf::Socket::Done) {

			sf::Uint16 x,y;

			if(!received >> x >> y) {
				cout << "error while reading data";
			}

			cout << "got " << x << "and" << y;

			Window* win = Application::getInstance()->getWindow();


			sf::Shape rect = sf::Shape::Rectangle(x, y, 50, 50, sf::Color(255,255,255));

			win->addDrawableObject((sf::Drawable*)&rect);

			MoveRectEventHandler moveHandler(&rect);
			win->addEventHandler((EventHandler*) &moveHandler);

		}




}

