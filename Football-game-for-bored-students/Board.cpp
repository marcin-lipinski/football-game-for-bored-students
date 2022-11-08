#include "Board.h"
#include <iostream>

Board::Board(int h, int w) {
    width = w;
    height = h;
    initPoints();
}

void Board::initPoints() {
    points = (int**)malloc(sizeof(int**) * height);

    for (int i = 0; i < height + 1; i++) {
        points[i] = (int*)malloc(sizeof(int*) * (width + 1));
        for (int j = 0; j < width + 2; j++) {
            points[i][j] = 0;
            if (i == 1)points[i][j] = 1;
            if (i == height - 1)points[i][j] = 1;
            if (j == 0) points[i][j] = 1;
            if (j == width)points[i][j] = 1;
        }
    }

    points[1][4] = 0;
    points[height - 1][4] = 0;


    points[6][4] = 1;
      
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {        
            board[i][j] = Point();
            board[i][j].vertices[0] = i * 10 + j;
            board[i][j].vertices[1] = i * 10 + j + 1;
            board[i][j].vertices[2] = (i + 1) * 10 + j;
            board[i][j].vertices[3] = (i + 1) * 10 + j + 1;

            if (i > 1 )         board[i][j].upper = &board[i - 1][j];
            if (i < height - 2) board[i][j].bottom = &board[i + 1][j];
            if (j > 0)          board[i][j].left = &board[i][j - 1];
            if (j < width - 1)  board[i][j].right = &board[i][j + 1];

            if (i == 1) board[i][j].upper_connection = true;
            if (i + 2 == height) board[i][j].bottom_connection = true;
            if (j == 0) board[i][j].left_connection = true;
            if (j + 1 == width) board[i][j].right_connection = true;
        }
    }
    initFirstRow();
    initLastRow();
    currentPoint = board[6][4].vertices[0];
}

int Board::possibleMoves() {
    int result = 8;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (board[i][j].vertices[3] == currentPoint) {
                if (board[i][j].right_connection) result--;
                if (board[i][j].bottom_connection) result--;
                if (board[i][j].left_right_connection) result--;

                if (board[i][j].right != nullptr) {
                    if (board[i][j].right->bottom_connection) result--;
                    if (board[i][j].right->right_left_connection) result--;
                    if (board[i][j].right->bottom != nullptr) {
                        if (board[i][j].right->bottom->left_right_connection) result--;
                        if (board[i][j].right->bottom->left_connection) result--;
                    }
                    else result -= 2;
                }
                else result -= 4;
                if (board[i][j].bottom != nullptr) {
                    if (board[i][j].bottom->right_left_connection) result--;
                }
                else result -= 1;
            }
        }
    }
    std::cout << result << std::endl;
    return result;
}

void Board::initFirstRow() {
    for (int j = 0; j < width; j++) {
        board[0][j].upper_connection = true;
        board[0][j].bottom_connection = true;
        board[0][j].left_connection = true;
        board[0][j].right_connection = true;
        board[0][j].left_right_connection = true;
        board[0][j].right_left_connection = true;
    }

    board[0][(width - 1) / 2].right_left_connection = false;
    board[0][(width - 1) / 2].bottom_connection = false;
    board[0][(width - 1) / 2].right_connection = false;
    board[0][(width - 1) / 2].left_right_connection = false;

    board[0][(width - 1) / 2].bottom = &board[1][(width - 1) / 2];
    board[0][(width - 1) / 2].right = &board[1][width / 2];
    board[1][(width - 1) / 2].upper = &board[0][(width - 1) / 2];

    board[0][width / 2].right_left_connection = false;
    board[0][width / 2].bottom_connection = false;
    board[0][width / 2].left_connection = false;
    board[0][width / 2].left_right_connection = false;

    board[0][width / 2].bottom = &board[1][width / 2];
    board[0][width / 2].left = &board[1][(width - 1) / 2];
    board[1][width / 2].upper = &board[0][width / 2];
}

void Board::initLastRow() {
    for (int j = 0; j < width; j++) {
        board[height - 1][j].upper_connection = true;
        board[height - 1][j].bottom_connection = true;
        board[height - 1][j].left_connection = true;
        board[height - 1][j].right_connection = true;
        board[height - 1][j].left_right_connection = true;
        board[height - 1][j].right_left_connection = true;
    }

    board[height - 1][(width - 1) / 2].right_left_connection = false;
    board[height - 1][(width - 1) / 2].upper_connection = false;
    board[height - 1][(width - 1) / 2].right_connection = false;
    board[height - 1][(width - 1) / 2].left_right_connection = false;

    board[height - 1][(width - 1) / 2].upper = &board[height - 2][(width - 1) / 2];
    board[height - 1][(width - 1) / 2].right = &board[height - 1][width / 2];
    board[height - 2][(width - 1) / 2].bottom = &board[height - 1][(width - 1) / 2];

    board[height - 1][width / 2].right_left_connection = false;
    board[height - 1][width / 2].upper_connection = false;
    board[height - 1][width / 2].left_connection = false;
    board[height - 1][width / 2].left_right_connection = false;

    board[height - 1][width / 2].upper = &board[height - 2][width / 2];
    board[height - 1][width / 2].left = &board[height - 1][(width - 1) / 2];
    board[height - 2][width / 2].bottom = &board[height - 1][width / 2];
}

bool Board::isRightConnected(int i, int j) { return board[i][j].right_connection; }

bool Board::isBottomConnected(int i, int j) { return board[i][j].bottom_connection; }

bool Board::isUpperConnected(int i, int j) { return board[i][j].upper_connection; }

bool Board::isLeftConnected(int i, int j) { return board[i][j].left_connection; }

bool Board::isLeftRightConnected(int i, int j) { return board[i][j].left_right_connection; }

bool Board::isRightLeftConnected(int i, int j) { return board[i][j].right_left_connection; }

void Board::setRightConnected(int i, int j) { 
    board[i][j].right_connection = true; 
    if (board[i][j].right != nullptr) board[i][j].right->left_connection = true;
}

void Board::setBottomConnected(int i, int j) { 
    board[i][j].bottom_connection = true; 
    if (board[i][j].bottom != nullptr) board[i][j].bottom->upper_connection = true;
}

void Board::setLeftConnected(int i, int j) { 
    board[i][j].left_connection = true; 
    if (board[i][j].left != nullptr) board[i][j].left->right_connection = true;
}

void Board::setUpperConnected(int i, int j) { 
    board[i][j].upper_connection = true; 
    if (board[i][j].upper != nullptr) board[i][j].upper->bottom_connection = true;
}

void Board::setLeftRightConnected(int i, int j) { board[i][j].left_right_connection = true; }

void Board::setRightLeftConnected(int i, int j) { board[i][j].right_left_connection = true; }

int Board::getCurrentPoint() { return currentPoint; }

void Board::setCurrentPoint(int c) { currentPoint = c; }

int Board::getVertex(int i, int j, int v) { return board[i][j].vertices[v]; }