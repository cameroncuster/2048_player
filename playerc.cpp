#include <iostream>
#include <cmath>
#include <unordered_map>
#include "board.h"
#include "player.h"

using namespace std;

static unordered_map<int, int> log2Val = {
	{ 2, 1 }, { 4, 2 }, { 8, 3 }, { 16, 4 }, { 32, 5 }, { 64, 6 }, { 128, 7 },
	{ 256, 8 }, { 512, 9 }, { 1024, 10 }, { 2048, 11 }, { 4096, 12 }, { 8192, 13 },
	{ 16384, 14 }, { 32768, 15 }, { 65536, 16 }
}; // use the gcc compiler to handle this

static const vector<pair<pair<int, int>, pair<int, int>>> adj = {
	{ { 0, 0 }, { 0, 1 } },
	{ { 0, 1 }, { 0, 2 } },
	{ { 0, 2 }, { 0, 3 } },
	{ { 0, 3 }, { 1, 3 } },
	{ { 1, 3 }, { 1, 2 } },
	{ { 1, 2 }, { 1, 1 } },
	{ { 1, 1 }, { 1, 0 } }
	// the rest are primarily new spawns
}; // hard code the adjacent nodes

static const double wp[7] = { 10, 8, 7, 6.5, 3, 1, .7 };

static constexpr const ValidMove moves[4] = { LEFT, DOWN, RIGHT, UP };
static constexpr const double NINF = -1e9;

static constexpr const double w[4][4] = {
	{ 10, 8, 7, 6.5 },
	{ .5, .7, 1, 3 },
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 }
};

//static constexpr const int w[4][4] = { { 6, 5, 4, 3 }, { 5, 4, 3, 2 }, { 4, 3, 2, 1 }, { 3, 2, 1, 0 } };
//static constexpr const int w[4][4] = { { 4096, 2048, 1024, 512 }, { 2048, 1024, 512, 256 }, { 1024, 512, 256, 128 }, { 512, 256, 128, 64 } };
//static constexpr const int w[4][4] = { { 3, 2, 2, 3 }, { 2, 1, 1, 2 }, { 2, 1, 1, 2 }, { 3, 2, 2, 3 } };
//static constexpr const int w[4][4] = { { 15, 14, 13, 12 }, { 8, 9, 10, 11 }, { 7, 6, 5, 4 }, { 0, 1, 2, 3 } };
/*
   static constexpr const double w[4][4] = { { .135759, .121925, .102812, .099937 }, { .0997992,
   .0888405, .076711, .0724143 }, { .060654, .0562579, .037116, .0161889 }, { .0125498,
   .00992495, .00575871, .00335193 } };
 */

/*
   void spin( arr[4][4] ) const
   {
   int i, j;
   int a[4][4];
   for( i = 0; i < 4; i++ )
   for( j = 0; j < 4; j++ )
   a[i][j] = arr[i][j];

   for( i = 0; i < 4; i++ )
   for( j = 0; j < 4; j++ )
   arr[i][j] = a[4-j-1][i];
   }
 */

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
		return -( calculateScore( b ) - calculatePenalty( b ) ) * probability;

	if( !depth || probability < .02 )
		return calculateScore( b ) - calculatePenalty( b );

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

// organize the board in 2 or 4 ways as opposed to 8...
double Player::calculateScore( const Board &b ) const
{
	int i, j;
	double score = 0;
	for( i = 0; i < 4; i++ )
		for( j = 0; j < 4; j++ )
			score += w[i][j] * b.board[i][j];
	return score;
}

double Player::calculatePenalty( const Board &b ) const
{
	int i;
	double penalty = 0;
	for( i = 0; i < 7; i++ )
		penalty +=
			abs(
					log2Val[ b.board[ adj[i].first.first ][ adj[i].first.second ] ] -
					log2Val[ b.board[ adj[i].second.first ][ adj[i].second.second ] ]
			   ) *
			abs(
					log2Val[ b.board[ adj[i].first.first ][ adj[i].first.second ] ] -
					log2Val[ b.board[ adj[i].second.first ][ adj[i].second.second ] ]
			   ) *
			wp[i];
	return penalty;
}
