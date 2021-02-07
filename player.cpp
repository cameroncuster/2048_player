#include <iostream>
#include <cmath>
#include "board.h"
#include "player.h"

using namespace std;

static constexpr int deltaI[4] = { 1, 0, -1, 0 };
static constexpr int deltaJ[4] = { 0, 1, 0, -1 };
static constexpr ValidMove moves[4] = { LEFT, DOWN, RIGHT, UP };
static constexpr double NINF = -10e9;
//static constexpr int w[16] = { 6, 5, 4, 3, 5, 4, 3, 2, 4, 3, 2, 1, 3, 2, 1, 0 };
//static constexpr int w[4][4] = { { 6, 5, 4, 3 }, { 5, 4, 3, 2 }, { 4, 3, 2, 1 }, { 3, 2, 1, 0 } };
/*
static constexpr int w[16] = { 65536, 50625, 38416, 28561, 6561, 10000, 14641,
	20736, 4096, 2401, 1296, 625, 4, 16, 81, 256 };
	*/
static const double w[4][4] = { { .135759, .121925, .102812, .099937 }, { .0997992,
.0888405, .076711, .0724143 }, { .060654, .0562579, .037116, .0161889 }, { .0125498,
	.00992495, .00575871, .00335193 } };

Player::Player( ) { }

ValidMove Player::nextMove( const Board b ) const
{
	double score = NINF;
	double newScore;
	ValidMove move = NONE;
	for( ValidMove myMove : moves )
	{
		Board cpy( b );
		if( cpy.checkMove( myMove ) )
		{
			newScore = expectimax( cpy, 6, 0 );

			if( newScore > score )
			{
				move = myMove;
				score = newScore;
			}
		}
	}
	return move;
}

double Player::expectimax( Board b, int depth, bool agent ) const
{
	Board cpy( b );
	int i, j;
	double score = 0;
	int open = 0;

	if( b.isGameOver( ) )
		return 0;
		//return NINF;

	if( !depth )
		return b.getScore( ) * ( 16 - getTileCount( b ) );

	if( agent )
	{
		for( ValidMove myMove : moves )
			if( cpy.checkMove( myMove ) )
				score = max( expectimax( cpy, depth - 1, !agent ), score );
	}
	else
	{
		for( i = 0; i < 4; i++ )
		{
			for( j = 0; j < 4; j++ )
			{
				if( !b.board[i][j] )
				{
					cpy.board[i][j] = 2;
					score += 0.9 * expectimax( cpy, depth - 1, !agent );

					cpy.board[i][j] = 0;

					cpy.board[i][j] = 4;
					score += 0.1 * expectimax( cpy, depth - 1, !agent );

					open++;
				}
			}
		}
		if( !open )
			return 0;
			//return NINF;
		score /= open;
	}
	return score;
}

ValidMove Player::makeMove( const Board b ) const
{
	return nextMove( b );
}


int Player::getTileCount( const Board b ) const
{
	int i, j;
	int count = 0;
	for( i = 0; i < 4; i++ )
		for( j = 0; j < 4; j++ )
			if( b.board[i][j] )
				count++;
	return count;
}

double Player::calculateScore( const Board b ) const
{
	int i, j;
	double score = 0;
	for( i = 0; i < 4; i++ )
		for( j = 0; j < 4; j++ )
			score += w[i][j] * b.board[i][j];
	return score;
}

double Player::calculatePenalty( const Board b ) const
{
	int i, j, k;
	double penalty = 0;
	for( i = 0; i < 4; i++ )
		for( j = 0; j < 4; j++ )
			if( b.board[i][j] )
				for( k = 0; k < 4; k++ )
					if( i + deltaI[k] < 4 && j + deltaJ[k] < 4 &&
							i + deltaI[k] >= 0 && j + deltaJ[k] >= 0 )
						if( b.board[i + deltaI[k]][j + deltaJ[k]] )
							penalty += abs( b.board[i][j] -
									b.board[i + deltaI[k]][j + deltaJ[k]] );
	return penalty;
}
