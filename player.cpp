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

vector<int> inttoRow( const short &r )
{
	int i;
	vector<int> v( 4 );
	for( i = 0; i < 4; i++ )
	{
		v[i] = 1 << ( ( r >> ( 4 * i ) ) & 15 );
		if( v[i] == 1 )
			v[i] = 0;
	}
	return v;
}

Player::Player( )
{
	int i, j, k;

	Board b;
	btoi intboard( b );
	vector<int> row;
	vector<int> newRow( 4 );

	table.resize( 2, vector<short>( 1 << 16 ) );

	// BUILD TABLE
	for( i = 0; i < ( 1 << 16 ); i++ )
	{
		for( k = 0; k < 2; k++ )
		{
			row = inttoRow( i );
			for( j = 0; j < 4; j++ )
				b.board[0][j] = row[j];
			b.checkMove( k ? RIGHT : LEFT );
			for( j = 0; j < 4; j++ )
				newRow[j] = b.board[0][j];
			table[k][i] = intboard.rowtoint( newRow );
		}
	}
}

ValidMove Player::nextMove( const btoi b ) const
{
	int depth = 5;
	double score = NINF;
	double newScore;
	ValidMove move = NONE;
	for( ValidMove myMove : moves )
	{
		btoi cpy( b );
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

double Player::expectimax( btoi &b, int depth, bool agent, double probability ) const
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
			btoi cpy( b );
			if( cpy.checkMove( myMove ) )
				score = max( expectimax( cpy, depth - 1, !agent, probability ), score );
		}
	}
	else
	{
		score = 0;
		open = 0;
		for( i = 0; i < 4; i++ )
		{
			for( j = 0; j < 4; j++ )
			{
				if( !b.getVal( i, j ) )
				{
					b.setVal( i, j, 2 );
					score += 0.9 * expectimax( b, depth - 1, !agent, probability * .9 );

					b.setVal( i, j, 4 );
					score += 0.1 * expectimax( b, depth - 1, !agent, probability * .1 );

					// loop invariant
					b.setVal( i, j, 0 );

					open++;
				}
			}
		}
		//assert( open ); // game over if !open
		if( !open )
			return -calculateScore( b ) * probability;
		score /= open;
	}
	return score;
}

ValidMove Player::makeMove( const Board b ) const
{
	btoi intboard( b );
	return nextMove( intboard );
}

double Player::calculateScore( const btoi &b ) const
{
	int i, j;
	double score = 0;
	for( i = 0; i < 4; i++ )
		for( j = 0; j < 4; j++ )
			score += w[i][j] * ( double ) b.getVal( i, j );
	return score;
}
