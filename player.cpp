#include <iostream>
#include <cmath>
#include "player.h"

using namespace std;

static constexpr const double NINF = -10e9;
static constexpr const double w[4][4] = {
	{ 10, 8, 7, 6.5 },
	{ .5, .7, 1, 3 },
	{ -.5, -1.5, -1.8, -2 },
	{ -3.8, -3.7, -3.5, -3 }
};

Player::Player( ) { }

ValidMove Player::nextMove( const Board b ) const
{
	int open = 16 - getTileCount( b );
	int depth = open > 7 ? 5 : open > 3 ? 6 : 7;
	double score = NINF;
	double newScore;
	ValidMove move = NONE;
	for( ValidMove myMove : moves )
	{
		Board cpy( b );
		if( cpy.checkMove( myMove ) )
		{
			newScore = expectimax( cpy, depth, 0, 1 );

			if( newScore > score )
			{
				move = myMove;
				score = newScore;
			}
		}
	}
	return move;
}

double Player::expectimax( Board &b, int depth, bool agent, double probability ) const
{
	int i, j;
	double score = NINF;
	int open;

	if( b.isGameOver( ) )
		return -calculateScore( b ) * probability;

	if( !depth || probability < .02 )
		return calculateScore( b );

	if( agent )
	{
		for( ValidMove myMove : moves )
		{
			Board cpy( b );
			if( cpy.checkMove( myMove ) )
				score = max( expectimax( cpy, depth - 1, !agent, probability ), score );
		}
	}
	else
	{
		score = 0;
		open = 16 - getTileCount( b );
		for( i = 0; i < 4; i++ )
		{
			for( j = 0; j < 4; j++ )
			{
				if( !b.board[i][j] )
				{
					b.board[i][j] = 2;
					score += 0.9 * expectimax( b, depth - 1, !agent, probability * .9 );

					b.board[i][j] = 4;
					score += 0.1 * expectimax( b, depth - 1, !agent, probability * .1 );

					// loop invariant
					b.board[i][j] = 0;
				}
			}
		}
		score /= open;
	}
	return score;
}

ValidMove Player::makeMove( const Board b ) const
{
	return nextMove( b );
}


int Player::getTileCount( const Board &b ) const
{
	int i, j;
	int count = 0;
	for( i = 0; i < 4; i++ )
		for( j = 0; j < 4; j++ )
			if( b.board[i][j] )
				count++;
	return count;
}

double Player::calculateScore( const Board &b ) const
{
	int i, j;
	double score = 0;
	for( i = 0; i < 4; i++ )
		for( j = 0; j < 4; j++ )
			score += ( double ) w[i][j] * b.board[i][j];
	return score;
}
