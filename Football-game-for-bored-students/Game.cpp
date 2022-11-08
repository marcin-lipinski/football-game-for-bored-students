#include "Game.h"
#include "Frame.h"
#include "Board.h"
#include <iostream>

#define playerAColor 252, 3, 44
#define playerBColor 3, 78, 252
#define playerAwinning 3, 4, 5
#define playerBwinning	123, 124, 125

Game::Game() {
	board = new Board(12, 8);
	frame = new Frame(450, 700, 12, 8, board);
	playerA = new Player(frame, playerAColor, "images\\player1won.bmp", playerAwinning);
	playerB = new Player(frame, playerBColor, "images\\player2won.bmp", playerBwinning);
	currentPlayer = playerB;
	gameState = 0;
}

Game::~Game() {
	delete board;
	delete frame;
	delete playerA;
	delete playerB;
}

void Game::start() {
	while(gameState == 0)
	{
		changePlayer();
		playerTakeMove();
		checkWinner();
		checkTie();
	}
	resultOfGame();
	exit();
}

void Game::playerTakeMove() {
	gameState = currentPlayer->takeMove();
}

void Game::changePlayer() {
	if (currentPlayer == playerA) currentPlayer = playerB;
	else currentPlayer = playerA;
}

void Game::resultOfGame() {
	switch (gameState) {
		case 1:
			playerA->winner();
			waitingForExit();
			break;
		case 2:
			playerB->winner();
			waitingForExit();
			break;
		case 3:
			tie();
			waitingForExit();
			break;
		default:
			break;
	}
}

void Game::tie() {
	frame->showWinner("images\\tie.bmp");
}

void Game::checkWinner() {
	int x = board->getCurrentPoint();

	int* points = playerA->getWinningPoints();
	if (x == points[0] || x == points[1] || x == points[2]) gameState = 2;

	points = playerB->getWinningPoints();
	if (x == points[0] || x == points[1] || x == points[2]) gameState = 1;

}

void Game::checkTie() {
	if (board->possibleMoves() == 0) gameState = 3;
}

void Game::waitingForExit() {
	while (true) if (frame->isExitPressed()) break;;
}

void Game::exit() {
	frame->exit();
}
