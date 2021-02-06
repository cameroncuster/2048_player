#include <iostream>
#include <cmath>
#include "board.h"
#include "player.h"

using namespace std;

const double NINF = -10e9;

const int deltaI[4] = { 1, 0, -1, 0 };
const int deltaJ[4] = { 0, 1, 0, -1 };

Player::Player( )
{
	ValidMove moves[] = {LEFT, DOWN, RIGHT, UP};
}

ValidMove Player::bestMove( Board b )
{
	ValidMove moves[] = {LEFT, DOWN, RIGHT, UP};
	double score = NINF - 1;
	double newScore;
	ValidMove move = NONE;

	for( ValidMove myMove : moves )
	{
		Board cpy( b );
		if( cpy.checkMove( myMove ) )
		{
			newScore = bestScore( cpy, 6, 0 );

			if( newScore > score )
			{
				move = myMove;
				score = newScore;
			}
		}
	}

	return move;
}

double Player::bestScore( Board b, int depth, bool player )
{
	ValidMove moves[] = {LEFT, DOWN, RIGHT, UP};
	Board cpy( b );
	int i, j;
	double score = 0;
	int open = 0;

	if( b.isGameOver( ) )
		return NINF;

	if( !depth )
		return b.getScore( ) + getScore( b );

	if( player )
	{
		for( ValidMove myMove : moves )
			if( cpy.checkMove( myMove ) )
				score = max( bestScore( cpy, depth - 1, !player ), score );
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
					score += 0.9 * bestScore( cpy, depth - 1, !player );

					cpy.board[i][j] = 0;

					cpy.board[i][j] = 4;
					score += 0.1 * bestScore( cpy, depth - 1, !player );

					open++;
				}
			}
		}
		if( !open )
			return NINF;
		score /= open;
	}
	return score;
}

ValidMove Player::makeMove(const Board b)
{
	return bestMove( b );
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

double Player::getScore( Board b ) const
{
	int i, j;
	double score = 0;
	int w[4][4] = {
		{ 6, 5, 4, 3 },
		{ 5, 4, 3, 2 },
		{ 4, 3, 2, 1 },
		{ 3, 2, 1, 0 }
	};
	for( i = 0; i < 4; i++ )
		for( j = 0; j < 4; j++ )
			score += w[i][j] * b.board[i][j];
	return score;
}

double Player::penalty( Board b ) const
{
	int i, j, k;
	double penalty = 0;
	for( i = 0; i < 4; i++ )
		for( j = 0; j < 4; j++ )
			for( k = 0; k < 4; k++ )
				if( 0 < i + deltaI[i] < 4 && 0 < j + deltaJ[j] < 4 )
					penalty += abs( b.board[i][j] - b.board[i + deltaI[i]][j + deltaJ[j]] );
	return penalty;
}
