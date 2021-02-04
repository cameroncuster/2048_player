#include <iostream>
#include <cmath>
#include "board.h"
#include "player.h"

using namespace std;

Player::Player() { }

int Player::bestMove( Board b )
{
	int i;
	int score = 0;
	int newScore;
	int move = 0;

	for( i = 1; i < 5; i++ )
	{
		if( b.checkMove( ( ValidMove ) i ) )
		{
			newScore = bestScore( b, 6, 0 );

			if( newScore >= score )
			{
				move = i;
				score = newScore;
			}
		}
	}

	return move;
}

int Player::bestScore( Board b, int depth, bool player )
{
	int i, j;
	int score = 0;
	int open = 0;

	if( b.isGameOver( ) )
		return 0;

	if( !depth )
		return b.getScore( );

	if( player )
	{
		for( i = 1; i < 5; i++ )
			if( b.checkMove( ( ValidMove ) i ) )
				score = max( bestScore( b, depth - 1, !player ), b.getScore( ) );
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
					score += bestScore( b, depth - 1, player ) / 10;

					b.board[i][j] = 2;
					score += ( bestScore( b, depth - 1, player ) * 9 ) / 10;

					b.board[i][j] = 0;

					open++;
				}
			}
		}
		if( !open )
			return 0;
		score /= open;
	}

	return score;
}

ValidMove Player::makeMove(const Board b)
{
	return ( ValidMove ) bestMove( b );
}
