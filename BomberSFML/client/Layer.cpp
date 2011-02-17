/*
 * Layer.cpp
 *
 *  Created on: 2011-02-15
 *      Author: zapo
 */

#include "Layer.h"

Layer::Layer(sf::View & view) : view(&view) {
}

Layer::~Layer() {
	// TODO Auto-generated destructor stub
}

void Layer::addObject(sf::Drawable & object, unsigned int position) {

	if(position > objects.size()) {
		position = objects.size();
	}

	vector<sf::Drawable *>::iterator it = (objects.begin() + position);
	objects.insert(it, &object);
}

void Layer::removeObject(sf::Drawable & object) {

	vector<sf::Drawable *>::iterator begin = objects.begin();
	vector<sf::Drawable *>::iterator end = objects.end();

	vector<sf::Drawable *>::iterator found = std::find(begin, end, &object);

	if(found != end) {
		objects.erase(found);
	}

}

vector<sf::Drawable *> & Layer::getObjects() {
	return objects;
}

bool Layer::hasObject(const sf::Drawable & object) {

	vector<sf::Drawable *>::iterator begin = objects.begin();
	vector<sf::Drawable *>::iterator end = objects.end();

	return std::find(begin, end, &object) != end;

}

sf::View & Layer::getView() const {
	return *view;
}
