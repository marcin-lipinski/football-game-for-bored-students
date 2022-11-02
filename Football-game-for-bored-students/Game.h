#pragma once
#include "Board.h"
#include "Frame.h"
#include "Player.h"

class Game
{
private:
	Board *board;
	Frame *frame;
	Player *playerA, *playerB;
public:
	Game();
	void start();
};

