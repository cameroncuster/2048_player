#ifndef _BOARD_H_
#define _BOARD_H_
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <thread>

using namespace std;

enum ValidMove {NONE, LEFT, RIGHT, UP, DOWN};

typedef unsigned char byte;

class Board
{
   bool gameOver;
   int score;
   int maxCellVal;

public:
   Board();
   Board(const Board&);

   void printBoard() const;
   bool makeMove(ValidMove);
   bool checkMove(ValidMove);
   int getScore() const;
   int maxVal() const;
   bool isGameOver();
   
   int board[4][4];

private:
   void clearCanChange();
   bool addValue();
   bool anyValidMove();
   bool moveLeft();
   bool moveRight();
   bool moveUp();
   bool moveDown();
   void draw();
   void spin();
};

#endif
