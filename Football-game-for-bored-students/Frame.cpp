#include "Frame.h"
#include <SDL2/SDL.h>
#include <iostream>

#define BLACK 0, 0, 0
#define WHITE 255, 255, 255
#define GREY 203, 193, 199

Frame::Frame(double width, double height, double cols, double rows, Board *board) {
	this->board = board;
	initVariables(width, height, cols, rows);
	initWindow();
	createWindow();
	initBoard();
}

void Frame::initWindow() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::printf("error initializing SDL: %s\n", SDL_GetError());
	}
}

void Frame::createWindow() {
	win = SDL_CreateWindow("Tic Tac Toe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_BORDERLESS & SDL_WINDOW_SHOWN);
	ren = SDL_CreateRenderer(win, -1, 0);
}

void Frame::initVariables(double w, double h, double r, double c) {
	windowWidth = w;
	windowHeight = h;
	numberOfColumns = c;
	numberOfRows = r;
	boxWidth = w / (r + 2);
	boxHeight = h / (c + 2);
}

void Frame::initBoard() {
	SDL_SetRenderDrawColor(ren, WHITE, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(ren);
	SDL_SetRenderDrawColor(ren, GREY, 255);

	for (int i = 1; i <= numberOfRows + 1; i++) {
		SDL_RenderDrawLine(ren, i * boxWidth, boxHeight, i * boxWidth, numberOfColumns * boxHeight + boxHeight);
	}

	for (int i = 1; i <= numberOfColumns + 1; i++) {
		SDL_RenderDrawLine(ren, boxWidth, i * boxHeight, numberOfRows * boxWidth + boxWidth, i * boxHeight);
	}
	SDL_RenderPresent(ren);
}

void Frame::update() {
	if(positionArr[0][0] != positionArr[0][2] && positionArr[0][1] != positionArr[0][3]) SDL_SetRenderDrawColor(ren, WHITE, 255);
	else SDL_SetRenderDrawColor(ren, GREY, 255);
	SDL_RenderDrawLine(ren, positionArr[0][0], positionArr[0][1], positionArr[0][2], positionArr[0][3]);
	SDL_RenderPresent(ren);

	SDL_SetRenderDrawColor(ren, BLACK, 255);
	SDL_RenderDrawLine(ren, positionArr[1][0], positionArr[1][1], positionArr[1][2], positionArr[1][3]);
	SDL_RenderPresent(ren);
}


void Frame::handlePlayerChoice() {
	SDL_Event evnt;
	bool doRepeat = true;
	positionArrReset();

	while (doRepeat) {
		SDL_PollEvent(&evnt);
		if (evnt.type == SDL_QUIT) return;
		if (evnt.type == SDL_MOUSEMOTION) 
		{
			changeBoxInner(evnt.button.x, evnt.button.y);
		}
		if (evnt.type == SDL_MOUSEBUTTONDOWN) 
		{
			getActiveBoxIndexes();
		}
	}
}

void Frame::positionArrReset() {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) positionArr[i][j] = -1;
	}
}

void Frame::replacemeValuesInPositionArr() {
	positionArr[0][0] = positionArr[1][0];
	positionArr[0][1] = positionArr[1][1];
	positionArr[0][2] = positionArr[1][2];
	positionArr[0][3] = positionArr[1][3];
}

void Frame::addValuesToArr(double a, double b, double c, double d) {
	positionArr[1][0] = a;
	positionArr[1][1] = b;
	positionArr[1][2] = c;
	positionArr[1][3] = d;
}

void Frame::changeBoxInner(int x, int y)
{
	double boxY, boxX;
	for (int i = 0; i < numberOfColumns; i++){
		boxY = (i + 1) * boxHeight;
		for (int j = 0; j < numberOfRows; j++){
			boxX = (j + 1) * boxWidth;
			if (boxY <= y && boxY + boxHeight > y && boxX <= x && boxX + boxWidth > x) {
				double temp = (double)boxX + (double)boxWidth / 5;
				double temp2 = (double)boxX + 4 * ((double)boxWidth / 5);
				double temp3 = (double)boxY + (double)boxHeight / 5;
				double temp4 = (double)boxY + 4 * ((double)boxHeight / 5);
				double temp5 = (double)(boxX + (double)boxWidth / 2);
				double temp6 = (double)(boxY + (double)boxHeight / 2);
				replacemeValuesInPositionArr();

				if (x < temp && y > temp3 && y < temp4) {
					if (j == 0)continue;
					if (!board->isRightConnected(i, j - 1)) addValuesToArr(boxX, boxY, boxX, boxY + boxHeight);	// 0 1 0 1
				}

				if (x > temp2 && y > temp3 && y < temp4) {
					if (j + 1 == numberOfRows) continue;
					if (!board->isRightConnected(i, j)) addValuesToArr(boxX + boxWidth, boxY, boxX + boxWidth, boxY + boxHeight);
				}

				if (y < temp3) {
					if (i == 0)continue;
					if (!board->isBottomConnected(i - 1, j)) addValuesToArr(boxX, boxY, boxX + boxWidth, boxY);
				}

				if (y > temp4) {
					if (i + 1 == numberOfColumns) continue;
					if (!board->isBottomConnected(i, j)) addValuesToArr(boxX, boxY + boxHeight, boxX + boxWidth, boxY + boxHeight);
				}

				if ((x > temp && x < temp5 && y > temp3 && y < temp6) || (x > temp5 && x < temp2 && y > temp6 && y < temp4)) {
					if (!board->isLeftRightConnected(i, j)) addValuesToArr(boxX, boxY, boxX + boxWidth, boxY + boxHeight);
				}

				if ((x > temp5 && x < temp2 && y > temp3 && y < temp6) || (x > temp && x < temp5 && y > temp6 && y < temp4)) {
					if (!board->isRightLeftConnected(i, j)) addValuesToArr(boxX + boxWidth, boxY, boxX, boxY + boxHeight);
				}
				positions[0] = i; positions[1] = j;
				update();
			}
		}
	}
}

void Frame::getActiveBoxIndexes() {
	if (positionArr[0][0] != -1) {
		std::cout << positions[0] << " " << positions[1] << " " << positionArr[1][0] << " " << positionArr[0][1] << " " << positionArr[0][2] << " " << positionArr[0][3] << std::endl;
		board
	}
}