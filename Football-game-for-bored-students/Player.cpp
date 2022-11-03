#include "Player.h"
#include "Frame.h"
#include <iostream>

void Player::takeMove(Frame *frame) 
{
	frame->handlePlayerChoice();
}
