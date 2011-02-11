/*
 * Bullet.h
 *
 *  Created on: 2011-02-02
 *      Author: zapo
 */

#ifndef BULLET_H_
#define BULLET_H_

#include <SFML/Graphics.hpp>
#include "Character.h"

using namespace std;

class Bullet: public sf::Drawable {
public:

	enum Type {
		SMALL
	};

	Bullet(Type type);
	virtual ~Bullet();

	static bool init_static();
	bool init_dynamic();

private:

	virtual void Render(sf::RenderTarget &target) const;

	Type type;
	static sf::Image bulletImage;

	map<Character::Orientation, map<Type, Anim> > anim;
	map<Character::Orientation, map<Type, Anim> > * const panim;
};

#endif /* BULLET_H_ */
