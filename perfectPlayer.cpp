#include <iostream>
#include <cmath>
#include <climits>
#include "board.h"
#include "player.h"

using namespace std;

Player::Player() { }

int Player::bestMove( Board b, int depth )
{
	int i;
	int score = INT_MIN;
	int newScore;
	int move = 0;

	for( i = 1; i < 5; i++ )
	{
		if( b.checkMove( ( ValidMove ) i ) )
		{
			Board brd( b );
			brd.makeMove( ( ValidMove ) i );
			newScore = bestScore( brd, depth - 1, 0 );

			if( newScore > score )
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
	int score = INT_MIN;
	int newScore;
	int open = 0;

	if( !depth || b.isGameOver( ) )
		return b.getScore( );

	if( player )
	{
		for( i = 1; i < 5; i++ )
		{
			if( b.checkMove( ( ValidMove ) i ) )
			{
				Board brd( b );
				brd.makeMove( ( ValidMove ) i );
				score = max( bestScore( brd, depth - 1, !player ), score );
			}
		}
	}
	else
	{
		score = 0;
		for( i = 0; i < 4; i++ )
		{
			for( j = 0; j < 4; j++ )
			{
				if( !b.board[i][j] )
				{
					Board brd( b );

					brd.board[i][j] = 4;
					newScore = bestScore( brd, depth - 1, player );
					score += newScore / 10;

					brd.board[i][j] = 2;
					newScore = bestScore( brd, depth - 1, player );
					score += ( newScore * 9 ) / 10;

					open++;
				}
			}
		}
		score /= open;
	}

	return score;
}

ValidMove Player::makeMove(const Board b)
{
	Board brd( b );
	cout << bestMove( brd, 6 ) << endl;
	if( brd.checkMove( ( ValidMove ) bestMove( brd, 6 ) ) )
		return ( ValidMove ) bestMove( brd, 6 );
	return NONE;
}
