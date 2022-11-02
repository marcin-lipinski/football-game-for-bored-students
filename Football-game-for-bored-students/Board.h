#pragma once
#include "Point.h"


class Board
{
public:
	Board(int, int);
	bool isRightConnected(int, int);
	bool isBottomConnected(int, int);
	bool isLeftRightConnected(int, int);
	bool isRightLeftConnected(int, int);
	bool setRightConnected(int, int);
	bool setBottomConnected(int, int);
	bool setLeftRightConnected(int, int);
	bool setRightLeftConnected(int, int);
private:
	int width, height;
	Point board[11][9];
	void initPoints();
};

