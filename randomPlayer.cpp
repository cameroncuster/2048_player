#include "player.h"

Player::Player() { }

// This is a very simple player which will make random moves as long as it is
// able.
// 
// There is no logic in the moves
ValidMove Player::makeMove(const Board b)
{
   // Make a copy of the game board
   Board board(b);

   // Make an array of all the valid moves
   ValidMove moves[] = {LEFT, DOWN, RIGHT, UP};

   // Choose a random number to shuffle the valid moves
   int move = rand() % 24;

   // Permute the moves a random number of times
   while (move-- && next_permutation(moves, moves+4));

   // Try the moves in the new random order, choosing the first one that's valid
   for (ValidMove myMove : moves)
      if (board.checkMove(myMove))
         return myMove;

   // If we get here there are no random moves so just pick anything and the
   // game will exit.
   return NONE;
}
