/* 
 * File:   Window.h
 * Author: zapo
 *
 * Created on 12 janvier 2011, 09:27
 */

#ifndef WINDOW_H
#define	WINDOW_H

#include <SFML/Graphics.hpp>

class EventHandler;

using namespace std;

class Window : public sf::RenderWindow {

public:

	Window(int,int,int,string);
	Window(const Window& orig);
	virtual ~Window();
	vector<EventHandler*> getEventHandlers();
	void addEventHandler(EventHandler*);

	void run();



private:

	string title;
	int width;
	int height;
	int colors;


	vector<EventHandler*> eventHandlers;

};



#endif	/* WINDOW_H */

