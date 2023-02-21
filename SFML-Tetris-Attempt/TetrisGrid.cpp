#include "TetrisGrid.h"

void Goodie::destroyMatrixLine(Goodie::Matrix &matrix, int line) {
	if (line < 0 || line >= matrix.getLineCount())
		throw std::runtime_error("Attempted line is beyond the bounds of matrix.");

	delete[] matrix[line];
	for (int i = line; i > 0; i--) {
		matrix.matrix_ptr[i] = matrix.matrix_ptr[i - 1];
	}

	do {
		matrix.matrix_ptr[0] = new int[matrix.getColumnCount()];
	} while (matrix.matrix_ptr[0] == nullptr);

	for (int i = 0; i < matrix.getColumnCount(); i++) {
		matrix[0][i] = 0;
	}
}

TetrisGrid::TetrisGrid(sf::Vector2i grid_screen_coord, sf::Vector2i grid_size_par, sf::Vector2i grid_block_size) : transform_matrix(DIMENSION, DIMENSION, true, 0, 1, -1, 0), opposite_t_matrix(DIMENSION, DIMENSION, true, 0, -1, 1, 0), grid(grid_size_par.y, grid_size_par.x, false) {
	grid_size = grid_size_par;
	grid_s_c = grid_screen_coord;
	block.setSize((sf::Vector2f)grid_block_size);
}

void TetrisGrid::setFocusArea(sf::Vector2i pos, sf::Vector2i size) {
	fa_coord = pos;
	fa_size = size;
	origin_pos = fa_coord + sf::Vector2i(fa_size.x / 2 - 1, fa_size.y / 2 - 1);
}

bool TetrisGrid::changeFocusArea(Goodie::Matrix &&change_matrix) {
	if (fa_size.x != change_matrix.getColumnCount() || fa_size.y != change_matrix.getLineCount())
		return false;

	for (int i = 0; i < change_matrix.getLineCount(); i++) {
		for (int j = 0; j < change_matrix.getColumnCount(); j++) {
			grid[fa_coord.y + i][fa_coord.x + j] = change_matrix[i][j];
		}
	}

	return true;
}

bool TetrisGrid::rotateFocusArea() {
	sf::Vector2i vec1 = (transform_matrix * (fa_coord - origin_pos)).convertToSFMLVector2() + origin_pos, vec2 = (transform_matrix * ((fa_coord + fa_size - sf::Vector2i(1, 1)) - origin_pos)).convertToSFMLVector2() + origin_pos;
	
	if (vec1.x > vec2.x) {
		int temp = vec1.x;
		vec1.x = vec2.x;
		vec2.x = temp;
	}

	if (vec1.y > vec2.y) {
		int temp = vec1.y;
		vec1.y = vec2.y;
		vec2.y = temp;
	}

	if (vec1.x < 0 || vec2.x > grid_size.x - 1 || vec1.y < 0 || vec2.y > grid_size.y - 1)
		return false;

	Goodie::Matrix fa_content(fa_size.y, fa_size.x, false);
	for (int i = 0; i < fa_content.getLineCount(); i++) {
		for (int j = 0; j < fa_content.getColumnCount(); j++) {
			if (grid[fa_coord.y + i][fa_coord.x + j] == 1) {
				fa_content[i][j] = 0;
				continue;
			}
			fa_content[i][j] = grid[fa_coord.y + i][fa_coord.x + j];
			grid[fa_coord.y + i][fa_coord.x + j] = 0;
		}
	}

	for (int i = vec1.y; i <= vec2.y; i++) {
		for (int j = vec1.x; j <= vec2.x; j++) {
			sf::Vector2i fa_area_vec = (opposite_t_matrix * (sf::Vector2i(j, i) - origin_pos)).convertToSFMLVector2() + origin_pos - fa_coord;
			if (grid[i][j] != 0 && fa_content[fa_area_vec.y][fa_area_vec.x] != 0) {
				for (i = 0; i < fa_size.y; i++) {
					for (j = 0; j < fa_size.x; j++) {
						if (fa_content[i][j] == 0) continue;
						grid[fa_coord.y + i][fa_coord.x + j] = fa_content[i][j];
					}
				}
				return false;
			}
		}
	}

	for (int i = 0; i < fa_content.getLineCount(); i++) {
		for (int j = 0; j < fa_content.getColumnCount(); j++) {
			if (grid[fa_coord.y + i][fa_coord.x + j] == 1 || fa_content[i][j] == 0) continue;
			sf::Vector2i repl_pos = (transform_matrix * (fa_coord + sf::Vector2i(j, i) - origin_pos)).convertToSFMLVector2() + origin_pos;
			grid[repl_pos.y][repl_pos.x] = fa_content[i][j];
		}
	}

	fa_coord = vec1;

	int temp = fa_size.x;
	fa_size.x = fa_size.y;
	fa_size.y = temp;

	return true;
}

bool TetrisGrid::moveFocusArea(sf::Vector2i movement) {
	sf::Vector2i new_vec = fa_coord + movement;

	if (new_vec.x < 0 || new_vec.x + fa_size.x - 1 > grid_size.x - 1 || new_vec.y < 0 || new_vec.y + fa_size.y - 1 > grid_size.y - 1)
		return false;

	Goodie::Matrix fa_content(fa_size.y, fa_size.x, false);
	for (int i = 0; i < fa_content.getLineCount(); i++) {
		for (int j = 0; j < fa_content.getColumnCount(); j++) {
			if (grid[fa_coord.y + i][fa_coord.x + j] == 1) {
				fa_content[i][j] = 0;
				continue;
			}
			fa_content[i][j] = grid[fa_coord.y + i][fa_coord.x + j];
			grid[fa_coord.y + i][fa_coord.x + j] = 0;
		}
	}

	for (int i = 0; i < fa_size.y; i++) {
		for (int j = 0; j < fa_size.x; j++) {
			if (grid[new_vec.y + i][new_vec.x + j] != 0 && fa_content[i][j] != 0) {
				for (i = 0; i < fa_size.y; i++) {
					for (j = 0; j < fa_size.x; j++) {
						if (fa_content[i][j] == 0) continue;
						grid[fa_coord.y + i][fa_coord.x + j] = fa_content[i][j];
					}
				}
				return false;
			}
		}
	}

	fa_coord = new_vec;
	origin_pos += movement;
	
	for (int i = 0; i < fa_content.getLineCount(); i++) {
		for (int j = 0; j < fa_content.getColumnCount(); j++) {
			if (grid[fa_coord.y + i][fa_coord.x + j] == 1) continue;
			grid[fa_coord.y + i][fa_coord.x + j] += fa_content[i][j];
		}
	}

	return true;
}

void TetrisGrid::makeFocusAreaSolid() {
	for (int i = fa_coord.y; i < fa_coord.y + fa_size.y; i++) {
		for (int j = fa_coord.x; j < fa_coord.x + fa_size.x; j++) {
			if (grid[i][j] == 2) grid[i][j] = 1;
		}
	}
}

int TetrisGrid::lineCheck() {
	int i, j, line_count = 0;
	for (i = 0; i < grid.getLineCount(); i++) {
		for (j = 0; j < grid.getColumnCount(); j++) {
			if (grid[i][j] != 1)
				break;
		}
		if (j == grid.getColumnCount()) {
			line_count++;
			Goodie::destroyMatrixLine(grid, i);
		}
	}

	return line_count;
}

void TetrisGrid::clear() {
	for (int i = 0; i < grid_size.y; i++) {
		for (int j = 0; j < grid_size.x; j++) {
			grid[i][j] = 0;
		}
	}
}

//Block functions

void TetrisGrid::setBlockTexture(sf::Texture &texture) {
	block.setTexture(&texture);
}

//Render funcs

void TetrisGrid::render(sf::RenderWindow &target) {
	for (int i = 0; i < grid_size.y; i++) {
		for (int j = 0; j < grid_size.x; j++) {
			if (grid[i][j] == 0)
				continue;
			block.setPosition(grid_s_c.x + j * block.getSize().x, grid_s_c.y + i * block.getSize().y);
			target.draw(block);
		}
	}
}