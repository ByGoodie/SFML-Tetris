#ifndef GAME_H
#define GAME_H

#include "TetrisGrid.h"
#include "TetrisStructures.h"
#include <SFML/System/Clock.hpp>
#include <cstdlib>

#define RR(T, x) static_cast<T&&>(x)
#define TGRID_SIZE sf::Vector2i(10, 20)
#define TGRID_SCR_COORD sf::Vector2i(10, 15)
#define TGRID_BLOCK_SIZE sf::Vector2i(36, 36)

#define NSGRID_SCR_COORD sf::Vector2i(483, 90)
#define NSGRID_SIZE sf::Vector2i(4, 4)
#define NSGRID_BLOCK_SIZE TGRID_BLOCK_SIZE

extern std::unique_ptr<Goodie::Matrix> tStructs[TStructCount];

class Game {
private:
	//Variables
	sf::RenderWindow window;
	sf::Event evnt;

	sf::Clock dtClock;
	float time_for_fall, delta_time;
	
	TetrisGrid tGrid, next_struct_grid;
	sf::Text score_text;
	sf::Font fnt;
	sf::Sprite background_sprite;

	int next_struct, score;

	sf::Texture block_texture, background_texture;

	bool move_circumstance;

	char write_buff[100];

	//Functions
	void processEvents();
	void update(float dt);
	void render();
	
	void processKeyEvent(sf::Keyboard::Key key, bool isPressed);

public:
	Game();
	~Game();

	//Functions
	void run();
};

#endif
