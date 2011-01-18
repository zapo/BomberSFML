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

	void addDrawableObject(sf::Drawable*);
	vector<sf::Drawable*> getDrawableObjects();

	void run();



private:


	sf::Mutex drawableObjectsMutex;
	sf::Mutex eventHandlersMutex;
	string title;

	vector<EventHandler*> eventHandlers;
	vector<sf::Drawable*> drawableObjects;

	vector<sf::Drawable*>::iterator ido;
	vector<EventHandler*>::iterator iho;

};



#endif	/* WINDOW_H */

