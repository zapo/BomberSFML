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
#include "Layer.h"
#include <list>

class EventHandler;

using namespace std;

class Window: public sf::RenderWindow, public sf::Thread {

public:

	Window(const int, const int, const int, const string);
	Window(const Window& orig);
	virtual ~Window();
	list<EventHandler*> getEventHandlers() const;
	void addEventHandler(EventHandler&);

	void removeDrawableObject(sf::Drawable&, sf::View&, unsigned int, bool free = true);
	void addDrawableObject(const sf::Drawable&, sf::View&, unsigned int);
	map<sf::View*, map<unsigned int, list<const sf::Drawable*> > >getDrawableObjects() const;

	void addLayer(Layer&);

	Layer & GetMainLayer();
	Layer & GetInterfaceLayer();
	sf::View& GetInterfaceView();

	sf::Mutex drawableObjectsMutex;

private:

	virtual void Run();

	sf::View interface;
	Layer mainLayer;
	Layer interfaceLayer;

	sf::Mutex eventHandlersMutex;
	const string title;

	list<EventHandler*> eventHandlers;

	vector<Layer*> layers;
	vector<Layer*>::iterator lit;

	list<EventHandler*>::iterator iho;

};

#endif	/* WINDOW_H */

