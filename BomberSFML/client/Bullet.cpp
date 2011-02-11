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
	panim(&anim) {

}

Bullet::~Bullet() {
	// TODO Auto-generated destructor stub
}

bool Bullet::init_static() {

	bool loaded = bulletImage.LoadFromFile("build/client/resources/tank.png");
	bulletImage.CreateMaskFromColor(sf::Color(32, 212, 2));

	return loaded;
}

bool Bullet::init_dynamic() {

	anim[Character::DOWN][SMALL].addFrame(bulletImage, sf::IntRect(983, 42, 1027, 76));
	anim[Character::DOWN][SMALL].addFrame(bulletImage, sf::IntRect(954, 82, 962, 114));
	anim[Character::DOWN][SMALL].addFrame(bulletImage, sf::IntRect(936, 84, 948, 116));
}

void Bullet::Render(sf::RenderTarget &target) const {


}
