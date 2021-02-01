#include <iostream>
#include "board.h"

using namespace std;

#include "player.h"

Player::Player() { }

ValidMove Player::makeMove(const Board b)
{
   int maxScore = -1;
   ValidMove bestMove = LEFT;

   for (ValidMove move : {DOWN, LEFT, RIGHT, UP})
   {
      Board board(b);
      if (board.checkMove(move))
         if (board.getScore() > maxScore)
         {
            maxScore = board.getScore();
            bestMove = move;
         }
   }

   return bestMove;
}
