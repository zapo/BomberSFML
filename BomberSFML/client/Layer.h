/*
 * Layer.h
 *
 *  Created on: 2011-02-15
 *      Author: zapo
 */

#ifndef LAYER_H_
#define LAYER_H_
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

class Layer {
public:
	Layer(sf::View & view);

	void addObject(sf::Drawable &, unsigned int);
	void removeObject(sf::Drawable &);
	vector<sf::Drawable *> & getObjects() ;
	bool hasObject(const sf::Drawable & object);

	virtual ~Layer();
	sf::View & getView() const;

private:


	sf::View *view;
	vector<sf::Drawable *> objects;
};

#endif /* LAYER_H_ */
