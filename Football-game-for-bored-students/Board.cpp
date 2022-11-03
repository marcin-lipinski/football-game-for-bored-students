#include "Board.h"
#include <iostream>

Board::Board(int h, int w) {
    width = w;
    height = h;
    currentPoint = 64;
    initPoints();
}

void Board::initPoints() {
    for (int i = 0; i < height + 2; i++) {
        for (int j = 0; j < width; j++) {
            board[i][j] = Point();
            board[i][j].vertices[0] = i * 10 + j;
            board[i][j].vertices[1] = i * 10 + j + 1;
            board[i][j].vertices[2] = (i + 1) * 10 + j;
            board[i][j].vertices[3] = (i + 1) * 10 + j + 1;
            if (i == 0 || i == height + 1) {
                if (j < 3 || j > 4)
                {
                    board[i][j].bottom_connection = true;
                    board[i][j].left_right_connection = true;
                    board[i][j].right_connection = true;
                    board[i][j].right_left_connection = true;
                }
                if(j == 4) board[i][j].right_connection = true;
            }
        }
    }
}

bool Board::isRightConnected(int i, int j) { return board[i][j].right_connection; }

bool Board::isBottomConnected(int i, int j) { return board[i][j].bottom_connection; }

bool Board::isUpperConnected(int i, int j) { return board[i - 1][j].bottom_connection; }

bool Board::isLeftConnected(int i, int j) { return board[i][j - 1].right_connection; }

bool Board::isLeftRightConnected(int i, int j) { return board[i][j].left_right_connection; }

bool Board::isRightLeftConnected(int i, int j) { return board[i][j].right_left_connection; }

void Board::setRightConnected(int i, int j) { board[i][j].right_connection = true; }

void Board::setBottomConnected(int i, int j) { board[i][j].bottom_connection = true; }

void Board::setLeftConnected(int i, int j) { board[i][j - 1].right_connection = true; }

void Board::setUpperConnected(int i, int j) { board[i - 1][j].bottom_connection = true; }

void Board::setLeftRightConnected(int i, int j) { board[i][j].left_right_connection = true; }

void Board::setRightLeftConnected(int i, int j) { board[i][j].right_left_connection = true; }

int Board::getCurrentPoint() { return currentPoint; }

void Board::setCurrentPoint(int c) { currentPoint = c; }

int Board::getVertex(int i, int j, int v) { return board[i][j].vertices[v]; }