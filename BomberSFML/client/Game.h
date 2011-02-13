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
	Game(Window &window, Connection &connection);
	virtual ~Game();

	bool hasCharacter(long id) const;
	void addCharacter(long id, Character&);
	void deleteCharacter(long id);

	void setMainCharacter(Character&);
	Character& getMainCharacter() const;

	void run();

	Window& getWindow() const;
	Connection& getConnection() const;
	void loadRessources();


private:

	Window *window;
	Connection *connection;
	Character* mainCharacter;

	std::map<long, Character*> characters;

};

#endif /* GAME_H_ */
