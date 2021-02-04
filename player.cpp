#include <iostream>
#include <cmath>
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
	double score = 0.0;
	double newScore;
	ValidMove move = NONE;

	for( ValidMove myMove : moves )
	{
		if( b.checkMove( myMove ) )
		{
			newScore = bestScore( b, 5, 0 );

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
	int i, j;
	double score = 0.0;
	int open = 0;

	if( b.isGameOver( ) )
		return 0;

	if( !depth )
		return b.getScore( );

	if( player )
	{
		for( ValidMove myMove : moves )
			if( b.checkMove( myMove ) )
				score = max( bestScore( b, depth - 1, !player ), score );
	}
	else
	{
		for( i = 0; i < 4; i++ )
		{
			for( j = 0; j < 4; j++ )
			{
				if( !b.board[i][j] )
				{
					b.board[i][j] = 4;
					score += bestScore( b, depth - 1, player ) / 10.0;

					b.board[i][j] = 0;

					b.board[i][j] = 2;
					score += ( bestScore( b, depth - 1, player ) * 9.0 ) / 10.0;

					b.board[i][j] = 0;

					open++;
				}
			}
		}
		if( !open )
			return 0;
		score /= ( double ) open;
	}

	return score;
}

ValidMove Player::makeMove(const Board b)
{
	cout << bestMove( b ) << endl;
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
