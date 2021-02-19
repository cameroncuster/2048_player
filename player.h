#ifndef __PLAYER_H
#define __PLAYER_H
#include <list>
#include "board.h"
#include "btoi.h"

class Player
{
	Board board;

	double calculateScore( const Board &b ) const;
	double expectimax( Board &b, int depth, bool agent, double probability ) const;
	int getTileCount( const Board &b ) const;
	ValidMove nextMove( const Board b ) const;
	double moveWeight( const Board b, ValidMove move) const;

	public:
	Player( );
	ValidMove makeMove( const Board b ) const;
};

#endif
