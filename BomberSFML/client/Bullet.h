/*
 * Bullet.h
 *
 *  Created on: 2011-02-02
 *      Author: zapo
 */

#ifndef BULLET_H_
#define BULLET_H_

#include <SFML/Graphics.hpp>
#include <map>

//class Anim;

class Bullet: public sf::Drawable {
public:

	enum Type {
		SMALL
	};

	Bullet& operator=(Bullet& bullet);

	Bullet(Type type = SMALL/*, Character::Orientation orientation*/);
	virtual ~Bullet();

	static bool init_static();
	bool init_dynamic();

private:

	virtual void Render(sf::RenderTarget &target) const;

	Type type;
	static sf::Image bulletImage;

	//std::map<int, std::map<Type, Anim> > anim;
	//std::map<int, std::map<Type, Anim> > * const panim;

	//Character::Orientation orientation;
};

#endif /* BULLET_H_ */
