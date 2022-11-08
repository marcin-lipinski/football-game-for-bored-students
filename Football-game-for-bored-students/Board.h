#pragma once
#include "Point.h"


class Board
{
public:
	Board(int, int);
	bool isRightConnected(int, int);
	bool isBottomConnected(int, int);
	bool isLeftConnected(int, int);
	bool isUpperConnected(int, int);
	bool isLeftRightConnected(int, int);
	bool isRightLeftConnected(int, int);
	void setRightConnected(int, int);
	void setBottomConnected(int, int);
	void setLeftRightConnected(int, int);
	void setRightLeftConnected(int, int);
	void setLeftConnected(int, int);
	void setUpperConnected(int, int);
	int getCurrentPoint();
	void setCurrentPoint(int);
	int getVertex(int, int, int);
	int possibleMoves();
	int** points;
private:
	Point board[13][9];
	int width, height;
	int currentPoint;
	void initPoints();
	void initLastRow();
	void initFirstRow();
};

