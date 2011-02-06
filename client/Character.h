/*
 * Character.h
 *
 *  Created on: 2011-01-27
 *      Author: zapo
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <SFML/Graphics.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>
#include <iostream>
#include <map>
#include "Anim.h"

class Character : public sf::Drawable {
public:

	enum Orientation {
		UP,DOWN,LEFT,RIGHT, LEFTUP, LEFTDOWN, RIGHTUP, RIGHTDOWN
	};

	enum Action {
		MOVING, IDLEING
	};

	std::map<Action, std::map<Orientation, Anim> > * const getAnims() const {
		return panims;
	}

	void init_dynamic() {

		anims[IDLEING][DOWN].addFrame(tankImage, sf::IntRect(4, 39, 69, 119));
		anims[IDLEING][UP].addFrame(tankImage, sf::IntRect(4, 129, 68, 209));
		anims[IDLEING][LEFT].addFrame(tankImage, sf::IntRect(4, 320, 76, 393));
		anims[IDLEING][RIGHT].addFrame(tankImage, sf::IntRect(4, 230, 73, 304));
		anims[IDLEING][RIGHTUP].addFrame(tankImage, sf::IntRect(4, 418, 86, 495));
		anims[IDLEING][LEFTUP].addFrame(tankImage, sf::IntRect(4, 418, 86, 495), true);
		anims[IDLEING][RIGHTDOWN].addFrame(tankImage, sf::IntRect(4, 514, 86, 598));
		anims[IDLEING][LEFTDOWN].addFrame(tankImage, sf::IntRect(4, 514, 86, 598), true);

		anims[MOVING][DOWN].addFrame(tankImage, sf::IntRect(107, 42, 174, 119));
		anims[MOVING][DOWN].addFrame(tankImage, sf::IntRect(183, 42, 250, 119));
		anims[MOVING][DOWN].addFrame(tankImage, sf::IntRect(259, 42, 326, 119));
		anims[MOVING][DOWN].addFrame(tankImage, sf::IntRect(335, 42, 402, 119));

		anims[MOVING][UP].addFrame(tankImage, sf::IntRect(109, 131, 178, 208));
		anims[MOVING][UP].addFrame(tankImage, sf::IntRect(183, 131, 252, 208));
		anims[MOVING][UP].addFrame(tankImage, sf::IntRect(259, 131, 328, 208));
		anims[MOVING][UP].addFrame(tankImage, sf::IntRect(334, 131, 403, 208));

		anims[MOVING][RIGHT].addFrame(tankImage, sf::IntRect(107, 230, 179, 305));
		anims[MOVING][RIGHT].addFrame(tankImage, sf::IntRect(186, 230, 257, 305));
		anims[MOVING][RIGHT].addFrame(tankImage, sf::IntRect(267, 230, 338, 305));
		anims[MOVING][RIGHT].addFrame(tankImage, sf::IntRect(348, 230, 419, 305));

		anims[MOVING][LEFT].addFrame(tankImage, sf::IntRect(107, 320, 184, 396));
		anims[MOVING][LEFT].addFrame(tankImage, sf::IntRect(188, 320, 266, 396));
		anims[MOVING][LEFT].addFrame(tankImage, sf::IntRect(270, 320, 348, 396));
		anims[MOVING][LEFT].addFrame(tankImage, sf::IntRect(357, 320, 435, 396));

		anims[MOVING][RIGHTUP].addFrame(tankImage, sf::IntRect(100, 417, 186, 496));
		anims[MOVING][RIGHTUP].addFrame(tankImage, sf::IntRect(187, 417, 273, 496));
		anims[MOVING][RIGHTUP].addFrame(tankImage, sf::IntRect(274, 418, 360, 497));
		anims[MOVING][RIGHTUP].addFrame(tankImage, sf::IntRect(364, 417, 450, 496));

		anims[MOVING][LEFTUP].addFrame(tankImage, sf::IntRect(100, 417, 186, 496), true);
		anims[MOVING][LEFTUP].addFrame(tankImage, sf::IntRect(187, 417, 273, 496), true);
		anims[MOVING][LEFTUP].addFrame(tankImage, sf::IntRect(274, 418, 360, 497), true);
		anims[MOVING][LEFTUP].addFrame(tankImage, sf::IntRect(364, 417, 450, 496), true);

		anims[MOVING][RIGHTDOWN].addFrame(tankImage, sf::IntRect(95, 513, 180, 598));
		anims[MOVING][RIGHTDOWN].addFrame(tankImage, sf::IntRect(192, 513, 277, 598));
		anims[MOVING][RIGHTDOWN].addFrame(tankImage, sf::IntRect(288, 513, 373, 598));
		anims[MOVING][RIGHTDOWN].addFrame(tankImage, sf::IntRect(382, 513, 467, 598));

		anims[MOVING][LEFTDOWN].addFrame(tankImage, sf::IntRect(95, 513, 180, 598), true);
		anims[MOVING][LEFTDOWN].addFrame(tankImage, sf::IntRect(192, 513, 277, 598), true);
		anims[MOVING][LEFTDOWN].addFrame(tankImage, sf::IntRect(288, 513, 373, 598), true);
		anims[MOVING][LEFTDOWN].addFrame(tankImage, sf::IntRect(382, 513, 467, 598), true);
	}

	Character(long id = 0, Orientation orientation = DOWN, Action currentAction = IDLEING) :
		sf::Drawable(), id(id), orientation(orientation), currentAction(currentAction), panims(&anims) {

	}

	Character(const Character &character) :
		sf::Drawable(), id(character.id), orientation(character.orientation), currentAction(character.currentAction), panims(&anims) {
		this->SetPosition(character.GetPosition());

	}

	Character& operator=(const Character &character) {

		this->id = character.id;
		this->SetPosition(character.GetPosition());
		this->orientation = character.orientation;

		this->currentAction = character.currentAction;


		//only update our animation if we have more than one frame

		if(anims[currentAction][orientation].getFrames().size() > 1) {
			anims[currentAction][orientation].update();
		}

	}

	virtual ~Character() {

	}
	void shoot() const {
		std::cout << "I'm goliath shooting at you david !!!!" << std::endl;
	}

	void move(const sf::Vector2f & position) {

		this->SetPosition(position);
		currentAction = Character::MOVING;
	}

	long getId() const {
		return id;
	}


	static bool init_static() {

		bool loaded = tankImage.LoadFromFile("build/client/resources/tank.png");
		tankImage.CreateMaskFromColor(sf::Color(32, 212, 2));

		return loaded;
	}



	Character::Orientation getOrientation() const {
		return orientation;
	}
	void setOrientation(Orientation orientation) {
		this->orientation = orientation;
	}

	Action getCurrentAction() const {
		return currentAction;
	}

	void setCurrentAction(Action action) {
		currentAction = action;
	}

private:

	Action currentAction;
	std::size_t currentFrame;

	static sf::Image tankImage;

	friend class boost::serialization::access;
	template <class Archive>
	void save(Archive &ar, const unsigned int version) const {

		sf::Vector2f position = this->GetPosition();

		ar & id;
		ar & position;
		ar & orientation;
		ar & currentAction;
	}

	template <class Archive>
	void load(Archive &ar, const unsigned int version) {

		sf::Vector2f position;

		ar & id;
		ar & position;
		ar & orientation;
		ar & currentAction;

		this->SetPosition(position);
	}

	BOOST_SERIALIZATION_SPLIT_MEMBER();


	virtual void Render(sf::RenderTarget &target) const {

		std::map<Action, std::map<Orientation, Anim> > * const anims = getAnims();

		if(anims != NULL) {
			target.Draw((*anims)[currentAction][orientation].getCurrentFrame());

		}

	}

	Orientation orientation;

	long id;

	sf::Sprite idleLeft;
	sf::Sprite idleRight;
	sf::Sprite idleUp;
	sf::Sprite idleDown;
	sf::Sprite idleRightUp;
	sf::Sprite idleRightDown;
	sf::Sprite idleLeftUp;
	sf::Sprite idleLeftDown;


	std::map<Action, std::map<Orientation, Anim> > * const panims;

	std::map<Action, std::map<Orientation, Anim> > anims;




};


#endif /* CHARACTER_H_ */
