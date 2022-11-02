#include "Player.h"
#include "Frame.h"
#include <iostream>

void Player::takeMove(Frame *frame) 
{
	frame->handlePlayerChoice();
	int i, j, a, b;
	std::cin >> i >> j >> a >> b;
}
