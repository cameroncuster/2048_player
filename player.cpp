#include <iostream>
#include <cmath>
#include "board.h"
#include "player.h"

using namespace std;

const int arr[16] = { 2, 4, 8, 16, 32, 64, 128, 256, 1024, 2048, 4096, 8192,
	16384, 32768, 65536, 131072 };

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
	double w[4][4] = {
		{ .135759, .121925, .102812, .099937 },
		{ .0997992, .0888405, .076711, .0724143 },
		{ .060654, .0562579, .037116, .0161889 },
		{ .0125498, .00992495, .00575871, .00335193 }
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
			if( b.board[i][j] )
				for( k = 0; k < 4; k++ )
					if( i + deltaI[k] < 4 && j + deltaJ[k] < 4 && i + deltaI[k] >= 0 && j + deltaJ[k] >= 0 )
						if( b.board[i + deltaI[k]][j + deltaJ[k]] )
							penalty += pow( abs( b.board[i][j] - b.board[i + deltaI[k]][j + deltaJ[k]] ), .5 );
	return penalty;
}
