#include "Frame.h"
#include <SDL2/SDL.h>
#include <iostream>

#define BLACK 0, 0, 0
#define WHITE 255, 255, 255
#define GREY 203, 193, 199

Frame::Frame(double width, double height, double rows, double cols, Board *board) {
	this->board = board;
	initVariables(width, height, rows, cols);
	initWindow();
	createWindow();
	renderBoard();
}

void Frame::initWindow() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) std::printf("error initializing SDL: %s\n", SDL_GetError());
}

void Frame::createWindow() {
	win = SDL_CreateWindow("Tic Tac Toe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)windowWidth, (int)windowHeight, SDL_WINDOW_BORDERLESS & SDL_WINDOW_SHOWN);
	ren = SDL_CreateRenderer(win, -1, 0);
}

void Frame::initVariables(double w, double h, double r, double c) {
	windowWidth = w;
	windowHeight = h;
	numberOfColumns = c;
	numberOfRows = r;
	boxWidth = w / (c + 2);
	boxHeight = h / (r + 2);
}

void Frame::renderBoard() {
	SDL_SetRenderDrawColor(ren, WHITE, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(ren);
	SDL_SetRenderDrawColor(ren, GREY, 255);

	//rendering a pitch
	for (int i = 2; i < numberOfRows + 1; i++) {
		SDL_RenderDrawLine(ren, boxWidth, i * boxHeight, (numberOfColumns + 1) * boxWidth, i * boxHeight);
	}

	for (int i = 1; i <= numberOfColumns + 1; i++) {
		SDL_RenderDrawLine(ren, i * boxWidth, 2 * boxHeight, i * boxWidth, numberOfRows * boxHeight);
	}
	// rendering goals
	SDL_RenderDrawLine(ren, 4 * boxWidth, boxHeight, 6 * boxWidth , boxHeight);
	SDL_RenderDrawLine(ren, 4 * boxWidth, boxHeight, 4 * boxWidth, 2 * boxHeight);
	SDL_RenderDrawLine(ren, 5 * boxWidth, boxHeight, 5 * boxWidth, 2 * boxHeight);
	SDL_RenderDrawLine(ren, 6 * boxWidth, boxHeight, 6 * boxWidth, 2 * boxHeight);

	SDL_RenderDrawLine(ren, 4 * boxWidth, 13 * boxHeight, 6 * boxWidth, 13 * boxHeight);
	SDL_RenderDrawLine(ren, 4 * boxWidth, 13 * boxHeight, 4 * boxWidth, 12 * boxHeight);
	SDL_RenderDrawLine(ren, 5 * boxWidth, 13 * boxHeight, 5 * boxWidth, 12 * boxHeight);
	SDL_RenderDrawLine(ren, 6 * boxWidth, 13 * boxHeight, 6 * boxWidth, 12 * boxHeight);

	//rendering a dot in mid of a pitch
	SDL_RenderDrawLineF(ren, windowWidth / 2 - 2, windowHeight / 2 - 2, windowWidth / 2 + 2, windowHeight / 2 - 2);
	SDL_RenderDrawLineF(ren, windowWidth / 2 - 2, windowHeight / 2 - 2, windowWidth / 2 - 2, windowHeight / 2 + 2);
	SDL_RenderDrawLineF(ren, windowWidth / 2 - 2, windowHeight / 2 + 2, windowWidth / 2 + 2, windowHeight / 2 + 2);
	SDL_RenderDrawLineF(ren, windowWidth / 2 + 2, windowHeight / 2 - 2, windowWidth / 2 + 2, windowHeight / 2 + 2);

	SDL_RenderPresent(ren);
}

void Frame::update() {
	if(positionArr[0][0] != positionArr[0][2] && positionArr[0][1] != positionArr[0][3]) SDL_SetRenderDrawColor(ren, WHITE, 255);
	else SDL_SetRenderDrawColor(ren, GREY, 255);
	SDL_RenderDrawLine(ren, positionArr[0][0], positionArr[0][1], positionArr[0][2], positionArr[0][3]);
	SDL_RenderPresent(ren);

	SDL_SetRenderDrawColor(ren, playerColor[0], playerColor[1], playerColor[2], 255);
	SDL_RenderDrawLine(ren, positionArr[1][0], positionArr[1][1], positionArr[1][2], positionArr[1][3]);
	SDL_RenderPresent(ren);
}

bool Frame::isExitPressed() {
	SDL_Event evnt;
	SDL_PollEvent(&evnt);
	if (evnt.type == SDL_QUIT) return true;
	else return false;
}


int Frame::handlePlayerChoice(int* color) {
	playerColor = color;
	SDL_Event evnt;
	positionArrReset();

	while (true) {
		SDL_PollEvent(&evnt);
		if (evnt.type == SDL_QUIT) {
			return -1;
		}
		if (evnt.type == SDL_MOUSEMOTION){
			changeBoxInner(evnt.button.x, evnt.button.y);
		}
		if (evnt.type == SDL_MOUSEBUTTONDOWN){
			if (getActiveBoxIndexes()) return 0;
			return 0;
		}
	}
}

void Frame::positionArrReset() {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) positionArr[i][j] = -1;
	}
}

void Frame::replacemeValuesInPositionArr(){
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
	if (board->getCurrentPoint() == v1 || board->getCurrentPoint() == v2) 
	{
		replacemeValuesInPositionArr();
		addValuesToArr(x1, y1, x2, y2);
		if (board->getCurrentPoint() == v1) temporaryPoint = v2;
		else temporaryPoint = v1;
	}
}

void Frame::changeBoxInner(int x, int y)
{
	double boxY, boxX;
	double a, b, c, d, e, f;
	double v0, v1, v2, v3;

	for (int i = 0; i < numberOfRows; i++){
		boxY = (i + 1) * boxHeight;
		for (int j = 0; j < numberOfColumns; j++){
			boxX = (j + 1) * boxWidth;
			if (boxY <= y && boxY + boxHeight > y && boxX <= x && boxX + boxWidth > x) {
				a = (double)boxX + (double)boxWidth / 5;
				b = (double)boxX + (double)boxWidth / 5 * 4;
				c = (double)boxY + (double)boxHeight / 5;
				d = (double)boxY + (double)boxHeight / 5 * 4;
				e = (double)boxX + (double)boxWidth / 2;
				f = (double)boxY + (double)boxHeight / 2;
				v0 = board->getVertex(i, j, 0);
				v1 = board->getVertex(i, j, 1);
				v2 = board->getVertex(i, j, 2);
				v3 = board->getVertex(i, j, 3);

				if (x < a && y > c && y < d && j != 0) {
					if (!board->isLeftConnected(i, j)) checkAndWrite(v0, v2, boxX, boxY, boxX, boxY + boxHeight);
				}

				if (x > b && y > c && y < d && j + 1 != numberOfRows) {
					if (!board->isRightConnected(i, j)) checkAndWrite(v1, v3, boxX + boxWidth, boxY, boxX + boxWidth, boxY + boxHeight);
				}

				if (y < c && (i != 0 || i + 1 != numberOfColumns)) {
					if (!board->isUpperConnected(i, j)) checkAndWrite(v0, v1, boxX, boxY, boxX + boxWidth, boxY);
				}

				if (y > d && i != numberOfColumns) {
					if (!board->isBottomConnected(i, j)) checkAndWrite(v2, v3, boxX, boxY + boxHeight, boxX + boxWidth, boxY + boxHeight);
				}

				if ((x > a && x < e && y > c && y < f) || (x > e && x < b && y > f && y < d)){
					if (!board->isLeftRightConnected(i, j)) checkAndWrite(v0, v3, boxX, boxY, boxX + boxWidth, boxY + boxHeight);
				}

				if ((x > e && x < b && y > c && y < f) || (x > a && x < e && y > f && y < d)) {
					if (!board->isRightLeftConnected(i, j)) checkAndWrite(v1, v2, boxX + boxWidth, boxY, boxX, boxY + boxHeight);
				}

				positions[0] = i; positions[1] = j;
				update();
			}
		}
	}
}

bool Frame::getActiveBoxIndexes() {
	if (positionArr[0][0] != -1) {
		if (positions[1] + 1 == positionArr[1][0] / boxWidth && positions[1] + 1 == positionArr[1][2] / boxWidth)		 board->setLeftConnected(positions[0], positions[1]);
		else if (positions[1] + 2 == positionArr[1][0] / boxWidth && positions[1] + 2 == positionArr[1][2] / boxWidth)	 board->setRightConnected(positions[0], positions[1]);
		else if (positions[0] + 1 == positionArr[1][1] / boxHeight && positions[0] + 1 == positionArr[1][3] / boxHeight) board->setUpperConnected(positions[0], positions[1]);
		else if (positions[0] + 2 == positionArr[1][1] / boxHeight && positions[0] + 2 == positionArr[1][3] / boxHeight) board->setBottomConnected(positions[0], positions[1]);
		else if (positions[1] + 1 == positionArr[1][0] / boxWidth)														 board->setLeftRightConnected(positions[0], positions[1]);
		else																											 board->setRightLeftConnected(positions[0], positions[1]);
	
		board->points[board->getCurrentPoint() / 10][board->getCurrentPoint() % 10] = 1;
		board->setCurrentPoint(temporaryPoint);
		positionArrReset();
		if (board->points[temporaryPoint / 10][temporaryPoint % 10] == 1) return false;
		else return true;
	}
	return false;
}

void Frame::showWinner(const char* uri) {
	SDL_Rect board;
	board.w = 250;
	board.h = 150;
	board.x = windowWidth / 2 - 125;
	board.y = windowHeight / 2 - 75;
	SDL_Surface* boardBMP = SDL_LoadBMP(uri);
	SDL_Texture* boardTexture = SDL_CreateTextureFromSurface(ren, boardBMP);

	SDL_Rect curtain;
	curtain.w = windowWidth;
	curtain.h = windowHeight;
	curtain.x = 0;
	curtain.y = 0;
	SDL_Surface* frameCurtain = SDL_CreateRGBSurface(0, windowWidth, windowHeight, 32, 255, 255, 255, 0);
	SDL_Texture* frameCurtainTexture = SDL_CreateTextureFromSurface(ren, frameCurtain);

	SDL_SetTextureBlendMode(frameCurtainTexture, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(frameCurtainTexture, 122);	

	SDL_RenderCopy(ren, frameCurtainTexture, NULL, &curtain);
	SDL_RenderCopy(ren, boardTexture, NULL, &board);
	SDL_RenderPresent(ren);
}

void Frame::exit() {
	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(ren);
	SDL_Quit();
}