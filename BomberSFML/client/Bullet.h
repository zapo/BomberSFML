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

class Bullet: public sf::Drawable {
public:

	enum Type {
		SMALL
	};

	Bullet(Type type);
	virtual ~Bullet();

	static bool init_static();

private:

	virtual void Render(sf::RenderTarget &target) const;

	Type type;
	static sf::Image bulletImage;

	std::map<Type, sf::Sprite> spriteMap;
	std::map<Type, sf::Sprite> * const pSpriteMap;
};

#endif /* BULLET_H_ */
