#pragma once
#include <SDL2/SDL.h>
#include "Board.h"

class Frame
{
private:
	SDL_Window* win;
	SDL_Renderer* ren;
	Board* board;
	double windowWidth, windowHeight;
	double boxWidth, boxHeight;
	double numberOfRows, numberOfColumns;
	double positionArr[2][4];
	double positions[2];
	int temporaryPoint;
	int* playerColor;

public:
	Frame(double, double, double, double, Board*);
	int handlePlayerChoice(int*);
	void showWinner(const char*);
	void exit();
	bool isExitPressed();
private:
	void initVariables(double, double, double, double);
	void initWindow();
	void createWindow();
	void renderBoard();
	void update();
	void changeBoxInner(int, int);
	void addValuesToArr(double, double, double, double);
	void replacemeValuesInPositionArr();
	bool getActiveBoxIndexes();
	void positionArrReset();
	void checkAndWrite(int, int, int, int, int, int);
	int side(int, int, int, int, int, int);
	bool nextMove();

	
};





