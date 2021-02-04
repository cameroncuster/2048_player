#include <iostream>
#include <cmath>
#include <cfloat>
#include "board.h"
#include "player.h"

using namespace std;

Player::Player( )
{
	ValidMove moves[] = {LEFT, DOWN, RIGHT, UP};
}

ValidMove Player::bestMove( Board b )
{
	ValidMove moves[] = {LEFT, DOWN, RIGHT, UP};
	double score = -DBL_MAX;
	double newScore;
	ValidMove move = NONE;

	for( ValidMove myMove : moves )
	{
		Board cpy( b );
		if( cpy.checkMove( myMove ) )
		{
			newScore = bestScore( cpy, 7, 0 );

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
		return -DBL_MAX;

	if( !depth )
		return b.getScore( );

	if( player )
	{
		for( ValidMove myMove : moves )
		{
			if( cpy.checkMove( myMove ) )
				score = max( bestScore( cpy, depth - 1, !player ), score );
		}
		return score;
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
					score += bestScore( cpy, depth - 1, player );
					cpy.board[i][j] = 0;
					open++;
				}
			}
		}
		if( !open )
			return -DBL_MAX;
		return score / open;
		/*
		   for( i = 0; i < 6; i++ )
		   {
		   addValue( cpy );
		   score += bestScore( cpy, depth - 1, player );
		   }
		   return score / 6;
		 */
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

bool Player::addValue( Board b ) const
{
	vector<int> emptyCells;
	for (int i = 0 ; i < 4 ; i++)
		for (int j = 0 ; j < 4 ; j++)
			if (!b.board[i][j])
				emptyCells.push_back(i * 4 + j);

	// If we found no empty cells, we can't place a new tile
	if (emptyCells.size() == 0) return false;

	// Pick a random empty cell
	int randCell = emptyCells[rand() % emptyCells.size()];

	// Set the random empty cell to either 2 or 4 at a 9:1 ratio
	b.board[randCell / 4][randCell % 4] = (rand() % 100 > 90) ? 4 : 2;

	return true;
}
