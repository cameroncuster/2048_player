#ifndef __PLAYER_H
#define __PLAYER_H
#include <list>
#include "board.h"

class Player
{
   Board board;
public:
   Player ();
   ValidMove makeMove(const Board);
private:
};

#endif
