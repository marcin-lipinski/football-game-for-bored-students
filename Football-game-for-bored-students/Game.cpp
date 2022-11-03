#include "Game.h"
#include "Frame.h"
#include "Board.h"
#include <iostream>

Game::Game() {
	board = new Board(12, 8);
	frame = new Frame(450, 700, 12, 8, board);
	playerA = new Player();
	playerB = new Player();
}

void Game::start() {
	while(true)
	{
		std::cout << "ruch gracza 1" << std::endl;
		playerA->takeMove(frame);
		std::cout << "ruch gracza 2" << std::endl;
		playerB->takeMove(frame);
	}
}
