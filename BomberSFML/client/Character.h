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
#include "Bullet.h"

class Character : public sf::Drawable {
public:

	enum Orientation {
		UP,DOWN,LEFT,RIGHT, LEFTUP, LEFTDOWN, RIGHTUP, RIGHTDOWN
	};

	enum Action {
		MOVING, IDLEING, SHOOTING
	};

	void init_dynamic();

	Character(long id = 0, Orientation orientation = DOWN, Action currentAction = IDLEING);
	Character(const Character &character);
	Character& operator=(const Character &character);
	virtual ~Character();

	void move(const sf::Vector2f & position);

	long getId() const;

	static bool init_static();

	Character::Orientation getOrientation() const;
	void setOrientation(Orientation orientation);

	Action getCurrentAction() const;
	void setCurrentAction(Action action);

private:

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

	virtual void Render(sf::RenderTarget &target) const;

	Orientation orientation;
	Action currentAction;

	long id;

	std::map<Action, std::map<Orientation, Anim> > * const panims;
	std::map<Action, std::map<Orientation, Anim> > anims;

	std::vector<Bullet> bullets;

	Bullet * loadedBullet;
	Bullet * const pLoadedBullet;

	static sf::Image tankImage;


};


#endif /* CHARACTER_H_ */
