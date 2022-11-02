#include "Game.h"
#include "Frame.h"
#include "Board.h"

Game::Game() {
	board = new Board(10, 8);
	frame = new Frame(450, 600, 8, 10, board);
	playerA = new Player();
	playerB = new Player();
}

void Game::start() {
	while(true)
	{
		playerA->takeMove(frame);
		playerB->takeMove(frame);
	}
}
