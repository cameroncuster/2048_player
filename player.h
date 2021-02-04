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
		ValidMove bestMove( Board b );
		double bestScore( Board b, int depth, bool player );
		int getTileCount( const Board b ) const;
		bool addValue( Board b ) const;
		ValidMove moves[];
};

#endif
