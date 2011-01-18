/*
 * Application.cpp
 *
 *  Created on: 2011-01-17
 *      Author: zapo
 */

#include "Application.h"
#include <SFML/Network.hpp>


Application* Application::instance = 0;

Application::Application() {

}

Application* Application::getInstance() {

	if(!instance) {
		instance = new Application;
	}

	return instance;
}



Application::~Application() {
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

}



