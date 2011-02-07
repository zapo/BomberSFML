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

	bool hasCharacter(long id);
	void addCharacter(long id, Character&);
	void deleteCharacter(long id);

	void setIsRunning(bool);

	void setMainCharacter(Character&);
	Character& getMainCharacter();

	void run();

	Window& getWindow();
	Connection& getConnection();
	void loadRessources();

private:

	bool isRunning;

	Window *window;
	Connection *connection;
	Character* mainCharacter;

	std::map<long, Character*> characters;


};

#endif /* GAME_H_ */
