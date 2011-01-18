/*
 * Application.h
 *
 *  Created on: 2011-01-17
 *      Author: zapo
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <SFML/Network.hpp>

class Connection;

class Window;

class Application {
public:
	static Application *getInstance();
	void setWindow(Window*);
	Window* getWindow();
	virtual ~Application();
	void setConnection(Connection*);
private:
	Application();
	static Application *instance;

	Window *window;
	Connection *connection;
};


#endif /* APPLICATION_H_ */


