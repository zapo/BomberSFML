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

	Window(const int, const int, const int, const string);
	Window(const Window& orig);
	virtual ~Window();
	list<const EventHandler*> getEventHandlers() const;
	void addEventHandler(EventHandler&);

	void removeDrawableObject(sf::Drawable&, unsigned int, bool free = true);
	void addDrawableObject(const sf::Drawable&, unsigned int);
	std::map<unsigned int, list<const sf::Drawable*> > getDrawableObjects() const;

	void setIsFrameratePrinted(bool print, const sf::Vector2f position, float refresh = 1.f);

	void updateFramerate();

	sf::Mutex drawableObjectsMutex;

private:

	virtual void Run();

	float framerateRefresh;
	bool isFrameratePrinted;

	sf::String framerate;
	sf::Clock framerateClock;

	sf::Mutex eventHandlersMutex;
	const string title;

	sf::View interface;

	list<const EventHandler*> eventHandlers;
	std::map<unsigned int, std::list<const sf::Drawable*> > drawableObjects;

	map<unsigned int, list<const sf::Drawable*> >::iterator ido;
	list<const EventHandler*>::iterator iho;

};

#endif	/* WINDOW_H */

