/*
 * Game.h
 *
 *  Created on: 2011-01-30
 *      Author: zapo
 */

#ifndef GAME_H_
#define GAME_H_

#include <map>
#include <SFML/Graphics.hpp>

class Window;
class Connection;
class Character;
class EventHandler;

class Game {
public:
	Game( Window &window, Connection &connection);
	virtual ~Game();

	bool hasCharacter(const long id) const;
	void addCharacter(const long id, Character &);
	void addEventHandler(EventHandler & eventHandler);
	void deleteCharacter(const long id);

	void setMainCharacter(Character &);
    Character & getMainCharacter() const;

	void run();

	Window & getWindow() const;
	Connection & getConnection() const;
	void loadRessources();

	void updateMainView();
	void updateCharacters();
	void updateFramerate();
	void updateLatency();

	void setIsFrameratePrinted(bool print, const sf::Vector2f position, float refresh = 1.f);
	void setIsLatencyPrinted(bool print, const sf::Vector2f position, float refresh = 1.f);

	static void init_static();


private:

	Window * window;
	Connection * connection;
    Character * mainCharacter;

    float framerateRefresh, latencyRefresh;
    bool isFrameratePrinted, isLatencyPrinted;


    sf::String framerate, latency;
    sf::Clock framerateClock, latencyClock;

	std::map<long, Character*> characters;

	sf::Sprite mapSprite;
	static sf::Image mapImage;

};

#endif /* GAME_H_ */
