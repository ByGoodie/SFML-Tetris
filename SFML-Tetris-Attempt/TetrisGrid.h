#ifndef TETRIS_GRID_H
#define TETRIS_GRID_H

#include <SFML/Graphics.hpp>
#include "Vector.h"
#include "Matrix.h"

#define DIMENSION 2

class TetrisGrid {
private:
	Goodie::Matrix grid;
	sf::Vector2i grid_s_c, grid_size; //s_c = screen coordinate.
	sf::RectangleShape block;
	sf::Vector2i fa_coord, fa_size; //fa abbreviation stands for focus area. Used to manipulate the tetris structures on the screen.
	Goodie::Matrix transform_matrix, opposite_t_matrix; //The transform matrix rotates the vector 90 degrees clockwise rotation, opposite transform matrix rotates 90 degrees counterclockwise rotation.
	sf::Vector2i origin_pos;

public:
	TetrisGrid(sf::Vector2i grid_screen_coord, sf::Vector2i grid_size_par, sf::Vector2i grid_block_size);
	
	//Grid funcs
	void setFocusArea(sf::Vector2i pos, sf::Vector2i size);
	bool rotateFocusArea();
	bool moveFocusArea(sf::Vector2i movement);
	bool changeFocusArea(Goodie::Matrix &&change_matrix);
	void makeFocusAreaSolid();
	int lineCheck(); //the return value is the completed line count.
	void clear();

	//Block funcs
	void setBlockTexture(sf::Texture &texture);

	//Render funcs
	void render(sf::RenderWindow& target);
};

#endif
