#pragma once
#include "Frame.h"

class Player
{
public:
	Player(Frame*, int, int, int, const char*, int, int, int);
	int takeMove();
	int* getWinningPoints();
	void winner();
private:
	int color[3];
	int winningPoints[3];
	const char* winnerImage;
	Frame* frame;
};

