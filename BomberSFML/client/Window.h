/* 
 * File:   Window.h
 * Author: zapo
 *
 * Created on 12 janvier 2011, 09:27
 */

#ifndef WINDOW_H
#define	WINDOW_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <list>

class EventHandler;

using namespace std;

class Window : public sf::RenderWindow, public sf::Thread {

public:

	Window(int,int,int,string);
	Window(const Window& orig);
	virtual ~Window();
	list<EventHandler*> getEventHandlers();
	void addEventHandler(EventHandler*);

	void removeDrawableObject(sf::Drawable*);
	void addDrawableObject(sf::Drawable*);
	list<sf::Drawable*> getDrawableObjects();

	void setPrintFramerate(bool print);

	sf::Mutex drawableObjectsMutex;

private:

	virtual void Run();

	bool printFramerate;

	sf::String framerate;

	sf::Mutex eventHandlersMutex;
	string title;


	list<EventHandler*> eventHandlers;
	list<sf::Drawable*> drawableObjects;

	list<sf::Drawable*>::iterator ido;
	list<EventHandler*>::iterator iho;

};



#endif	/* WINDOW_H */

