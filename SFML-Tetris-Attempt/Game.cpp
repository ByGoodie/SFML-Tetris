#include "Game.h"

extern std::unique_ptr<Goodie::Matrix> tStructs[TStructCount];

Game::Game() :
	window(sf::VideoMode(750, 750), "Tetris"),
	tGrid(TGRID_SCR_COORD, TGRID_SIZE, TGRID_BLOCK_SIZE),
	next_struct_grid(NSGRID_SCR_COORD, NSGRID_SIZE, NSGRID_BLOCK_SIZE),
	move_circumstance(true)
{
	block_texture.loadFromFile("Resources/tetris_block.png");
	background_texture.loadFromFile("Resources/tetris_background.png");
	fnt.loadFromFile("Resources/8bitOperatorPlus-Regular.ttf");

	score_text.setCharacterSize(25);
	score_text.setPosition(sf::Vector2f(400.0f, 260.0f));
	score_text.setString(std::string("Score: 0"));
	score_text.setFont(fnt);

	background_sprite.setTexture(background_texture);
	background_sprite.setPosition(sf::Vector2f(0.0f, 0.0f));

	next_struct = std::rand() % TStructCount;
	tGrid.setFocusArea(sf::Vector2i((TGRID_SIZE.x - tStructs[next_struct]->getColumnCount()) / 2, 0), sf::Vector2i(tStructs[next_struct]->getColumnCount(), tStructs[next_struct]->getLineCount()));
	tGrid.changeFocusArea(RR(Goodie::Matrix, *tStructs[next_struct]));
	tGrid.setBlockTexture(block_texture);
	next_struct = std::rand() % TStructCount;

	next_struct_grid.setBlockTexture(block_texture);
	next_struct_grid.setFocusArea(sf::Vector2i((NSGRID_SIZE.x - tStructs[next_struct]->getColumnCount()) / 2, (NSGRID_SIZE.y - tStructs[next_struct]->getLineCount()) / 2), sf::Vector2i(tStructs[next_struct]->getColumnCount(), tStructs[next_struct]->getLineCount()));
	next_struct_grid.changeFocusArea(RR(Goodie::Matrix, *tStructs[next_struct]));
}

Game::~Game() {

}

void Game::processEvents() {
	while (window.pollEvent(evnt)) {
		if (evnt.type == sf::Event::Closed)
			window.close();
		else if (evnt.type == sf::Event::KeyPressed)
			processKeyEvent(evnt.key.code, true);
	}
}

void Game::update(float dt) {	
	if (move_circumstance == false) {
		tGrid.makeFocusAreaSolid();
		score += tGrid.lineCheck();
		sprintf_s(write_buff, 100, "Score: %d", score);
		score_text.setString(write_buff);

		tGrid.setFocusArea(sf::Vector2i((TGRID_SIZE.x - tStructs[next_struct]->getColumnCount()) / 2, 0), sf::Vector2i(tStructs[next_struct]->getColumnCount(), tStructs[next_struct]->getLineCount()));
		tGrid.changeFocusArea(RR(Goodie::Matrix, *tStructs[next_struct]));
		move_circumstance = true;
		next_struct = std::rand() % TStructCount;

		next_struct_grid.clear();
		next_struct_grid.setFocusArea(sf::Vector2i((NSGRID_SIZE.x - tStructs[next_struct]->getColumnCount()) / 2, (NSGRID_SIZE.y - tStructs[next_struct]->getLineCount()) / 2), sf::Vector2i(tStructs[next_struct]->getColumnCount(), tStructs[next_struct]->getLineCount()));
		next_struct_grid.changeFocusArea(RR(Goodie::Matrix, *tStructs[next_struct]));
	}
	else if (time_for_fall >= 1.0f && tGrid.moveFocusArea(sf::Vector2i(0, 1)) == false) {
		tGrid.makeFocusAreaSolid();
		score += tGrid.lineCheck();
		sprintf_s(write_buff, 100, "Score: %d", score);
		score_text.setString(write_buff);

		tGrid.setFocusArea(sf::Vector2i((TGRID_SIZE.x - tStructs[next_struct]->getColumnCount()) / 2, 0), sf::Vector2i(tStructs[next_struct]->getColumnCount(), tStructs[next_struct]->getLineCount()));
		tGrid.changeFocusArea(RR(Goodie::Matrix, *tStructs[next_struct]));
		next_struct = std::rand() % TStructCount;

		next_struct_grid.clear();
		next_struct_grid.setFocusArea(sf::Vector2i((NSGRID_SIZE.x - tStructs[next_struct]->getColumnCount()) / 2, (NSGRID_SIZE.y - tStructs[next_struct]->getLineCount()) / 2), sf::Vector2i(tStructs[next_struct]->getColumnCount(), tStructs[next_struct]->getLineCount()));
		next_struct_grid.changeFocusArea(RR(Goodie::Matrix, *tStructs[next_struct]));
	}
	if (time_for_fall >= 1.0f) time_for_fall -= 1.0f;
}

void Game::render() {
	window.clear();
	window.draw(background_sprite);
	window.draw(score_text);
	tGrid.render(window);
	next_struct_grid.render(window);
	window.display();
}

void Game::processKeyEvent(sf::Keyboard::Key key, bool isPressed) {
	if (isPressed) {
		switch (key) {
		case sf::Keyboard::Key::W:
			tGrid.rotateFocusArea();
			break;

		case sf::Keyboard::Key::A:
			tGrid.moveFocusArea(sf::Vector2i(-1, 0));
			break;

		case sf::Keyboard::Key::D:
			tGrid.moveFocusArea(sf::Vector2i(1, 0));
			break;

		case sf::Keyboard::Key::S:
			move_circumstance = tGrid.moveFocusArea(sf::Vector2i(0, 1));
			break;
		}
	}
}

void Game::run() {
	while (window.isOpen()) {
		processEvents();

		delta_time += dtClock.restart().asSeconds();
		time_for_fall += delta_time;
		update(delta_time);
		delta_time = 0.0f;

		render();
	}
}
