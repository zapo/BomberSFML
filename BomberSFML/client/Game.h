/*
 * Game.h
 *
 *  Created on: 2011-01-30
 *      Author: zapo
 */

#ifndef GAME_H_
#define GAME_H_

#include <map>

class Window;
class Connection;
class Character;

class Game {
public:
	Game( Window &window, Connection &connection);
	virtual ~Game();

	bool hasCharacter(const long id) const;
	void addCharacter(const long id, Character&);
	void deleteCharacter(const long id);

	void setMainCharacter(const Character&);
	const Character& getMainCharacter() const;

	void run();

	Window& getWindow() const;
	Connection& getConnection() const;
	void loadRessources();


private:

	Window *window;
	Connection *connection;
	const Character* mainCharacter;

	std::map<long, Character*> characters;

};

#endif /* GAME_H_ */
