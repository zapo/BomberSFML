/*
 * Anim.h
 *
 *  Created on: 2011-02-04
 *      Author: zapo
 */

#ifndef ANIM_H_
#define ANIM_H_

#include <SFML/Graphics/Sprite.hpp>

class Anim {
public:
	Anim() : currentFrame(0) {}

	void addFrame(const sf::Image& image, const sf::IntRect &subrect, bool flipx = false, bool flipy = false) {

		sf::Sprite frame = sf::Sprite(image);
		frame.SetSubRect(subrect);

		frame.FlipX(flipx);
		frame.FlipY(flipy);

		frames.push_back(frame);
	}

	void addFrame(const sf::Sprite& frame) {
		frames.push_back(frame);
	}


	const sf::Sprite getCurrentFrame() const {

		if(frames.size() > currentFrame) {

			return frames[currentFrame];

		} else {
			if(frames.size() > 0) {
				return frames[0];
			} else {
				return sf::Sprite();
			}
		}
	}

	void update() {

		if(currentFrame < (frames.size() - 1)) {
			currentFrame++;
		} else {
			currentFrame = 0;
		}
	}

	virtual ~Anim() {

	}

	std::vector<sf::Sprite> getFrames() const {
		return frames;
	}

private:
	std::vector<sf::Sprite> frames;
	int currentFrame;
};

#endif /* ANIM_H_ */
