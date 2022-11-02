#include "Board.h"
#include <iostream>

Board::Board(int h, int w) {
    width = w;
    height = h;
    initPoints();
}

void Board::initPoints() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            board[i][j] = Point();
            board[i][j].vertices[0] = i * 10 + j;
            board[i][j].vertices[1] = i * 10 + j + 1;
            board[i][j].vertices[2] = (i + 1) * 10 + j;
            board[i][j].vertices[3] = (i + 1) * 10 + j + 1;
            //std::cout << board[i][j].vertices[0] << " " << board[i][j].vertices[1] << " " << board[i][j].vertices[2] << " " << board[i][j].vertices[3] << std::endl;
            if (i > 0) board[i][j].upper = &board[i - 1][j];
            if (j > 0) board[i][j].left = &board[i][j - 1];
            if (j + 1 < width)       board[i][j].right = &board[i][j + 1];
            if (i + 1 < height) board[i][j].bottom = &board[i + 1][j];
        }
    }
}
bool Board::isRightConnected(int i, int j) {
    return board[i][j].right_connection;
}

bool Board::isBottomConnected(int i, int j) {
    return board[i][j].bottom_connection;
}

bool Board::isLeftRightConnected(int i, int j) {
    return board[i][j].left_right_connection;
}

bool Board::isRightLeftConnected(int i, int j) {
    return board[i][j].right_left_connection;
}

void Board::setRightConnected(int i, int j) {
    board[i][j].right_connection = true;
}

void Board::setBottomConnected(int i, int j) {
    board[i][j].bottom_connection = true;
}

void Board::setLeftRightConnected(int i, int j) {
    board[i][j].left_right_connection = true;
}

void Board::setRightLeftConnected(int i, int j) {
    board[i][j].right_left_connection = true;
}