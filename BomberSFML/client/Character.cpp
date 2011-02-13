/*
 * Character.cpp
 *
 *  Created on: 2011-02-13
 *      Author: zapo
 */

#include "Character.h"

Character::Character(long id, Orientation orientation, Action currentAction) :
	sf::Drawable(),
	id(id),
	orientation(orientation),
	currentAction(currentAction),
	panims(&anims),
	pLoadedBullet(loadedBullet),
	loadedBullet(&(bullets.back())) {

}

Character::Character(const Character &character) :
	sf::Drawable(),
	id(character.id),
	orientation(character.orientation),
	currentAction(character.currentAction),
	panims(&anims),
	pLoadedBullet(loadedBullet) {

	this->SetPosition(character.GetPosition());

}

Character& Character::operator=(const Character &character) {

	this->id = character.id;
	this->orientation = character.orientation;
	this->currentAction = character.currentAction;
	this->SetPosition(character.GetPosition());

	//only update our animation if we have more than one frame

	if(anims[currentAction][orientation].getFrames().size() > 1) {
		anims[currentAction][orientation].update();
	}
}

Character::~Character() {
}

void Character::move(const sf::Vector2f & position) {
	this->SetPosition(position);
	currentAction = Character::MOVING;
}

long Character::getId() const {
	return id;
}

Character::Orientation Character::getOrientation() const {
	return orientation;
}
void Character::setOrientation(Orientation orientation) {
	this->orientation = orientation;
}

Character::Action Character::getCurrentAction() const {
	return currentAction;
}

void Character::setCurrentAction(Action action) {
	currentAction = action;
}

void Character::Render(sf::RenderTarget &target) const {

	if(panims != NULL) {
		target.Draw((*panims)[currentAction][orientation].getCurrentFrame());

		if(currentAction == SHOOTING) {

			//target.Draw(Bullet(Bullet::SMALL, orientation));

		}
	}
}

void Character::init_dynamic() {

	anims[IDLEING][DOWN].addFrame(tankImage, sf::IntRect(106, 39, 175, 120));
	anims[IDLEING][UP].addFrame(tankImage, sf::IntRect(2, 130, 69, 211));
	anims[IDLEING][LEFT].addFrame(tankImage, sf::IntRect(2, 320, 76, 393));
	anims[IDLEING][RIGHT].addFrame(tankImage, sf::IntRect(2, 230, 75, 306));

	anims[IDLEING][RIGHTUP].addFrame(tankImage, sf::IntRect(2, 418, 86, 495));
	anims[IDLEING][LEFTUP].addFrame(tankImage, sf::IntRect(2, 418, 86, 495),
			true);
	anims[IDLEING][RIGHTDOWN].addFrame(tankImage, sf::IntRect(2, 514, 86, 598));
	anims[IDLEING][LEFTDOWN].addFrame(tankImage, sf::IntRect(2, 514, 86, 598),
			true);

	anims[MOVING][DOWN].addFrame(tankImage, sf::IntRect(106, 39, 175, 120));
	anims[MOVING][DOWN].addFrame(tankImage, sf::IntRect(182, 39, 251, 120));
	anims[MOVING][DOWN].addFrame(tankImage, sf::IntRect(258, 39, 327, 120));
	anims[MOVING][DOWN].addFrame(tankImage, sf::IntRect(334, 39, 403, 120));

	anims[MOVING][UP].addFrame(tankImage, sf::IntRect(110, 130, 177, 211));
	anims[MOVING][UP].addFrame(tankImage, sf::IntRect(184, 130, 251, 211));
	anims[MOVING][UP].addFrame(tankImage, sf::IntRect(260, 130, 327, 211));
	anims[MOVING][UP].addFrame(tankImage, sf::IntRect(335, 130, 402, 211));

	anims[MOVING][RIGHT].addFrame(tankImage, sf::IntRect(106, 230, 179, 306));
	anims[MOVING][RIGHT].addFrame(tankImage, sf::IntRect(185, 230, 259, 306));
	anims[MOVING][RIGHT].addFrame(tankImage, sf::IntRect(266, 230, 340, 306));
	anims[MOVING][RIGHT].addFrame(tankImage, sf::IntRect(348, 230, 422, 306));

	anims[MOVING][LEFT].addFrame(tankImage, sf::IntRect(107, 320, 184, 396));
	anims[MOVING][LEFT].addFrame(tankImage, sf::IntRect(188, 320, 266, 396));
	anims[MOVING][LEFT].addFrame(tankImage, sf::IntRect(270, 320, 348, 396));
	anims[MOVING][LEFT].addFrame(tankImage, sf::IntRect(357, 320, 435, 396));

	anims[MOVING][RIGHTUP].addFrame(tankImage, sf::IntRect(100, 417, 186, 496));
	anims[MOVING][RIGHTUP].addFrame(tankImage, sf::IntRect(187, 417, 273, 496));
	anims[MOVING][RIGHTUP].addFrame(tankImage, sf::IntRect(274, 418, 360, 497));
	anims[MOVING][RIGHTUP].addFrame(tankImage, sf::IntRect(364, 417, 450, 496));

	anims[MOVING][LEFTUP].addFrame(tankImage, sf::IntRect(100, 417, 186, 496),
			true);
	anims[MOVING][LEFTUP].addFrame(tankImage, sf::IntRect(187, 417, 273, 496),
			true);
	anims[MOVING][LEFTUP].addFrame(tankImage, sf::IntRect(274, 418, 360, 497),
			true);
	anims[MOVING][LEFTUP].addFrame(tankImage, sf::IntRect(364, 417, 450, 496),
			true);

	anims[MOVING][RIGHTDOWN].addFrame(tankImage, sf::IntRect(95, 513, 180, 598));
	anims[MOVING][RIGHTDOWN].addFrame(tankImage,
			sf::IntRect(192, 513, 277, 598));
	anims[MOVING][RIGHTDOWN].addFrame(tankImage,
			sf::IntRect(288, 513, 373, 598));
	anims[MOVING][RIGHTDOWN].addFrame(tankImage,
			sf::IntRect(382, 513, 467, 598));

	anims[MOVING][LEFTDOWN].addFrame(tankImage, sf::IntRect(95, 513, 180, 598),
			true);
	anims[MOVING][LEFTDOWN].addFrame(tankImage,
			sf::IntRect(192, 513, 277, 598), true);
	anims[MOVING][LEFTDOWN].addFrame(tankImage,
			sf::IntRect(288, 513, 373, 598), true);
	anims[MOVING][LEFTDOWN].addFrame(tankImage,
			sf::IntRect(382, 513, 467, 598), true);

	anims[SHOOTING][DOWN].addFrame(tankImage, sf::IntRect(486, 37, 555, 117));
	anims[SHOOTING][DOWN].addFrame(tankImage, sf::IntRect(574, 37, 643, 117));
	anims[SHOOTING][DOWN].addFrame(tankImage, sf::IntRect(658, 37, 727, 117));
	anims[SHOOTING][DOWN].addFrame(tankImage, sf::IntRect(745, 37, 814, 117));

	anims[SHOOTING][UP].addFrame(tankImage, sf::IntRect(487, 127, 554, 206));
	anims[SHOOTING][UP].addFrame(tankImage, sf::IntRect(570, 127, 637, 206));
	anims[SHOOTING][UP].addFrame(tankImage, sf::IntRect(652, 127, 719, 206));
	anims[SHOOTING][UP].addFrame(tankImage, sf::IntRect(734, 127, 801, 206));

	anims[SHOOTING][RIGHT].addFrame(tankImage, sf::IntRect(486, 226, 562, 302));
	anims[SHOOTING][RIGHT].addFrame(tankImage, sf::IntRect(568, 226, 644, 302));
	anims[SHOOTING][RIGHT].addFrame(tankImage, sf::IntRect(651, 226, 727, 302));
	anims[SHOOTING][RIGHT].addFrame(tankImage, sf::IntRect(734, 226, 814, 302));

	anims[SHOOTING][LEFT].addFrame(tankImage, sf::IntRect(486, 314, 562, 392));
	anims[SHOOTING][LEFT].addFrame(tankImage, sf::IntRect(568, 314, 644, 392));
	anims[SHOOTING][LEFT].addFrame(tankImage, sf::IntRect(651, 314, 727, 392));
	anims[SHOOTING][LEFT].addFrame(tankImage, sf::IntRect(734, 314, 814, 392));

	for (int i = 0; i < 100; i++) {

		//bullets.push_back(Bullet(Bullet::SMALL, this->orientation));

	}
}

bool Character::init_static() {

	bool loaded = tankImage.LoadFromFile("build/client/resources/tank.png");
	tankImage.CreateMaskFromColor(sf::Color(32, 212, 2));

	return loaded;
}



