/*
 * Application.cpp
 *
 *  Created on: 2011-01-17
 *      Author: zapo
 */

#include "Application.h"
#include <SFML/Network.hpp>
#include "Connection.h"
#include <iostream>

Application* Application::instance = NULL;

Application::Application() {

}

Application* Application::getInstance() {

	if(!instance) {
		std::cout << "Application instanciation" << std::endl;
		instance = new Application;
	}

	return instance;
}



Application::~Application() {

	connection->Wait();

	delete instance;
}

void Application::setWindow(Window *win) {
	window = win;
}

Window* Application::getWindow() {
	return window;
}

void Application::setConnection(Connection *connection) {

	this->connection = connection;
	this->connection->Launch();

}



