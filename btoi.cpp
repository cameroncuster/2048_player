#include "board.h"
#include "btoi.h"
#include <cmath>

using namespace std;

vector<int> arrtovec( const int *arr )
{
	int i;
	vector<int> v( 4 );
	for( i = 0; i < 4; i++ )
		v[i] = arr[i];
	return v;
}

btoi::btoi( const Board arr, vector<vector<short>> sTable )
{
	int i;
	table = sTable;
	b = 0;
	for( i = 3; i >= 0; i-- )
	{
		b <<= 16;
		b |= rowtoint( arrtovec( arr.board[i] ) );
	}
}

bool btoi::isGameOver( )
{
	long long cpy = b;
	for( ValidMove move : moves )
		if( checkMove( move ) )
		{
			b = cpy;
			return 0;
		}
	return 1;
}

bool btoi::checkMove( ValidMove move )
{
	int i;
	short r, c;
	long long newr, newc;
	long long cpy = 0;
	bool valid = 0;
	switch( move )
	{
		case UP:
			for( i = 0; i < 4; i++ )
			{
				c = getCol( i );
				newc = table[0][c];
				if( c != newc )
					valid = 1;
				placeCol( cpy, newc, i );
			}
			break;
		case DOWN:
			for( i = 0; i < 4; i++ )
			{
				c = getCol( i );
				newc = table[1][c];
				if( c != newc )
					valid = 1;
				placeCol( cpy, newc, i );
			}
			break;
		case LEFT:
			for( i = 0; i < 4; i++ )
			{
				r = getRow( i );
				newr = table[0][r];
				if( r != newr )
					valid = 1;
				cpy |= newr << ( 16 * i );
			}
			break;
		case RIGHT:
			for( i = 0; i < 4; i++ )
			{
				r = getRow( i );
				newr = table[1][r];
				if( r != newr )
					valid = 1;
				cpy |= newr << ( 16 * i );
			}
			break;
		default:
			break;
	}
	b = cpy;
	return valid;
}

long long btoi::getBoard( ) const
{
	return b;
}

short btoi::getRow( const int &row ) const
{
	return b >> ( 16 * row );
}

short btoi::getCol( const int &col ) const
{
	int i;
	short colVal = 0;
	long long temp = b >> ( 4 * col );
	for( i = 0; i < 4; i++ )
		colVal |= ( ( temp >> ( 16 * i ) ) & 15 ) << ( 4 * i );
	return colVal;
}

short btoi::rowtoint( const vector<int> &row ) const
{
	int i;
	short r = 0;
	for( i = 3; i >= 0; i-- )
	{
		r <<= 4;
		if( row[i] )
			r |= ( int ) log2( row[i] );
	}
	return r;
}

void btoi::placeCol( long long &bc, short colVal, const int &col ) const
{
	int i;
	for( i = 0; i < 4; i++ )
		bc |= ( ( ( long long ) colVal >> ( 4 * i ) ) & 15 ) << ( 16 * i + 4 * col );
}
