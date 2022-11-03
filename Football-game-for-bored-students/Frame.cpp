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
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) std::printf("error initializing SDL: %s\n", SDL_GetError());
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
	boxHeight = h / (c + 4);
}

void Frame::initBoard() {
	SDL_SetRenderDrawColor(ren, WHITE, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(ren);
	SDL_SetRenderDrawColor(ren, GREY, 255);

	for (int i = 1; i <= numberOfRows + 1; i++) {
		SDL_RenderDrawLine(ren, i * boxWidth, 2 * boxHeight, i * boxWidth, numberOfColumns * boxHeight + 2 * boxHeight);
	}

	for (int i = 1; i <= numberOfColumns + 1; i++) {
		SDL_RenderDrawLine(ren, boxWidth, i * boxHeight + boxHeight, numberOfRows * boxWidth + boxWidth, i * boxHeight + boxHeight);
	}

	SDL_RenderDrawLine(ren, 4 * boxWidth, boxHeight, 6 * boxWidth , boxHeight);
	SDL_RenderDrawLine(ren, 4 * boxWidth, boxHeight, 4 * boxWidth, 2 * boxHeight);
	SDL_RenderDrawLine(ren, 5 * boxWidth, boxHeight, 5 * boxWidth, 2 * boxHeight);
	SDL_RenderDrawLine(ren, 6 * boxWidth, boxHeight, 6 * boxWidth, 2 * boxHeight);

	SDL_RenderDrawLine(ren, 4 * boxWidth, 13 * boxHeight, 6 * boxWidth, 13 * boxHeight);
	SDL_RenderDrawLine(ren, 4 * boxWidth, 13 * boxHeight, 4 * boxWidth, 12 * boxHeight);
	SDL_RenderDrawLine(ren, 5 * boxWidth, 13 * boxHeight, 5 * boxWidth, 12 * boxHeight);
	SDL_RenderDrawLine(ren, 6 * boxWidth, 13 * boxHeight, 6 * boxWidth, 12 * boxHeight);


	SDL_SetRenderDrawColor(ren, BLACK, 255);
	SDL_Rect rect;
	
	rect.x = windowWidth / 2 + 1.5;
	rect.y = windowHeight / 2 + 1.5;
	rect.w = 5;
	rect.h = 5;
	SDL_RenderFillRect(ren, &rect);

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
			doRepeat = false;
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

void Frame::checkAndWrite(int v1, int v2, int x1, int y1, int x2, int y2) {
	if (board->getCurrentPoint() == v1 || board->getCurrentPoint() == v2) {
		replacemeValuesInPositionArr();
		addValuesToArr(x1, y1, x2, y2);
		if (board->getCurrentPoint() == v1) temporaryPoint = v2;
		else temporaryPoint = v1;
	}
}

void Frame::changeBoxInner(int x, int y)
{
	double boxY, boxX;
	double temp1, temp2, temp3, temp4, temp5, temp6;
	for (int i = 0; i < numberOfColumns + 2; i++){
		boxY = (i + 1) * boxHeight;
		for (int j = 0; j < numberOfRows; j++){
			boxX = (j + 1) * boxWidth;
			if (boxY <= y && boxY + boxHeight > y && boxX <= x && boxX + boxWidth > x) {
				temp1 = (double)boxX + (double)boxWidth / 5;
				temp2 = (double)boxX + (double)boxWidth / 5 * 4;
				temp3 = (double)boxY + (double)boxHeight / 5;
				temp4 = (double)boxY + (double)boxHeight / 5 * 4;
				temp5 = (double)boxX + (double)boxWidth / 2;
				temp6 = (double)boxY + (double)boxHeight / 2;

				if (x < temp1 && y > temp3 && y < temp4) {
					if (j == 0)continue;
					if (!board->isLeftConnected(i, j)) checkAndWrite(board->getVertex(i, j, 0), board->getVertex(i, j, 2), boxX, boxY, boxX, boxY + boxHeight);
				}

				if (x > temp2 && y > temp3 && y < temp4) {
					if (j + 1 == numberOfRows) continue;
					if (!board->isRightConnected(i, j)) checkAndWrite(board->getVertex(i, j, 1), board->getVertex(i, j, 3), boxX + boxWidth, boxY, boxX + boxWidth, boxY + boxHeight);
				}

				if (y < temp3) {
					if (i == 0)continue;
					if (!board->isUpperConnected(i, j)) checkAndWrite(board->getVertex(i, j, 0), board->getVertex(i, j, 1), boxX, boxY, boxX + boxWidth, boxY);
				}

				if (y > temp4) {
					if (i + 1 == numberOfColumns) continue;
					if (!board->isBottomConnected(i, j)) checkAndWrite(board->getVertex(i, j, 2), board->getVertex(i, j, 3), boxX, boxY + boxHeight, boxX + boxWidth, boxY + boxHeight);
				}

				if ((x > temp1 && x < temp5 && y > temp3 && y < temp6) || (x > temp5 && x < temp2 && y > temp6 && y < temp4)){
					if (!board->isLeftRightConnected(i, j)) checkAndWrite(board->getVertex(i, j, 0), board->getVertex(i, j, 3), boxX, boxY, boxX + boxWidth, boxY + boxHeight);
				}

				if ((x > temp5 && x < temp2 && y > temp3 && y < temp6) || (x > temp1 && x < temp5 && y > temp6 && y < temp4)) {
					if (!board->isRightLeftConnected(i, j)) checkAndWrite(board->getVertex(i, j, 1), board->getVertex(i, j, 2), boxX + boxWidth, boxY, boxX, boxY + boxHeight);
				}
				positions[0] = i; positions[1] = j;
				update();
			}
		}
	}
}

void Frame::getActiveBoxIndexes() {
	if (positionArr[0][0] != -1) {
		if (positions[1] + 1 == positionArr[1][0] / boxWidth && positions[1] + 1 == positionArr[1][2] / boxWidth)		 board->setLeftConnected(positions[0], positions[1]);
		else if (positions[1] + 2 == positionArr[1][0] / boxWidth && positions[1] + 2 == positionArr[1][2] / boxWidth)	 board->setRightConnected(positions[0], positions[1]);
		else if (positions[0] + 1 == positionArr[1][1] / boxHeight && positions[0] + 1 == positionArr[1][3] / boxHeight) board->setUpperConnected(positions[0], positions[1]);
		else if (positions[0] + 2 == positionArr[1][1] / boxHeight && positions[0] + 2 == positionArr[1][3] / boxHeight) board->setBottomConnected(positions[0], positions[1]);
		else if (positions[1] + 1 == positionArr[1][0] / boxWidth)														 board->setLeftRightConnected(positions[0], positions[1]);
		else																											 board->setRightLeftConnected(positions[0], positions[1]);
		board->setCurrentPoint(temporaryPoint);
	}
}