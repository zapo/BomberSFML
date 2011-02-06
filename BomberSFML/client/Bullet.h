/*
 * Bullet.h
 *
 *  Created on: 2011-02-02
 *      Author: zapo
 */

#ifndef BULLET_H_
#define BULLET_H_

#include <SFML/Graphics/Drawable.hpp>

class Bullet: public sf::Drawable {
public:
	Bullet();
	virtual ~Bullet();

private:

	virtual void Render(sf::RenderTarget &target) const;
};

#endif /* BULLET_H_ */
