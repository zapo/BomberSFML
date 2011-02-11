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

class Window: public sf::RenderWindow, public sf::Thread {

public:

	Window(int, int, int, string);
	Window(const Window& orig);
	virtual ~Window();
	list<EventHandler*> getEventHandlers();
	void addEventHandler(EventHandler*);

	void removeDrawableObject(sf::Drawable*, unsigned int, bool free = true);
	void addDrawableObject(sf::Drawable*, unsigned int);
	std::map<unsigned int, list<sf::Drawable*> > getDrawableObjects() const;

	void setIsFrameratePrinted(bool print, sf::Vector2f position, float refresh = 1.f);

	void updateFramerate();

	sf::Mutex drawableObjectsMutex;

private:

	virtual void Run();

	float framerateRefresh;
	bool isFrameratePrinted;

	sf::String framerate;
	sf::Clock framerateClock;

	sf::Mutex eventHandlersMutex;
	string title;

	sf::View interface;

	list<EventHandler*> eventHandlers;
	std::map<unsigned int, std::list<sf::Drawable*> > drawableObjects;

	map<unsigned int, list<sf::Drawable*> >::iterator ido;
	list<EventHandler*>::iterator iho;

};

#endif	/* WINDOW_H */

