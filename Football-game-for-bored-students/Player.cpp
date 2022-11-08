#include "Player.h"
#include "Frame.h"
#include <iostream>

Player::Player(Frame* frame, int r, int g, int b, const char* src, int w1, int w2, int w3) {
	this->frame = frame;
	color[0] = r;
	color[1] = g;
	color[2] = b;
	winnerImage = src;
	winningPoints[0] = w1;
	winningPoints[1] = w2;
	winningPoints[2] = w3;
}

int Player::takeMove() 
{
	return frame->handlePlayerChoice(color);
}

int* Player::getWinningPoints() {
	return winningPoints;
}

void Player::winner() {
	frame->showWinner(winnerImage);
}
