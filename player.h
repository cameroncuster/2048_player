#ifndef __PLAYER_H
#define __PLAYER_H
#include <list>
#include "board.h"
#include "btoi.h"

class Player
{
	Board board;

	double calculateScore( const btoi &b ) const;
	double expectimax( btoi &b, int depth, bool agent, double probability ) const;
	ValidMove nextMove( const btoi b ) const;

	public:
	Player( );
	ValidMove makeMove( const Board b ) const;
};

#endif
