/*
 * Bullet.cpp
 *
 *  Created on: 2011-02-02
 *      Author: zapo
 */

#include "Bullet.h"

sf::Image Bullet::bulletImage;

Bullet::Bullet(Type type) :
	sf::Drawable(),
	type(type),
	pSpriteMap(&spriteMap) {

}

Bullet::~Bullet() {
	// TODO Auto-generated destructor stub
}

bool Bullet::init_static() {

	bool loaded = bulletImage.LoadFromFile("build/client/resources/tank.png");
	bulletImage.CreateMaskFromColor(sf::Color(32, 212, 2));

	return loaded;
}

void Bullet::Render(sf::RenderTarget &target) const {


}
