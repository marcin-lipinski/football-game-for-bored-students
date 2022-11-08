#pragma once
#include "Board.h"
#include "Frame.h"
#include "Player.h"

class Game
{
private:
	Board *board;
	Frame *frame;
	Player *playerA, *playerB, *currentPlayer;
	int gameState;
public:
	Game();
	~Game();
	void start();
	void exit();
	void resultOfGame();
	void waitingForExit();
	void tie();
	void changePlayer();
	void checkWinner();
	void checkTie();
	void playerTakeMove();
};

