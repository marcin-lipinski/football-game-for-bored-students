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

public:
	Frame(double, double, double, double, Board*);
	int handlePlayerChoice();
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
};





