#include <iostream>
#include "Game.h"

extern std::unique_ptr<Goodie::Matrix> tStructs[TStructCount];

int main(void) {
	std::srand(time(NULL));
	initTStructures();

	Game game;
	game.run();

	return 0;
}
