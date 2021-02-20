#include "board.h"
#include "btoi.h"
#include <cmath>

using namespace std;

vector<vector<unsigned short>> table;

static unordered_map<unsigned long long , unsigned long long> log2Val = {
	{ 0, 0 }, { 2, 1 }, { 4, 2 }, { 8, 3 }, { 16, 4 }, { 32, 5 }, { 64, 6 }, { 128, 7 },
	{ 256, 8 }, { 512, 9 }, { 1024, 10 }, { 2048, 11 }, { 4096, 12 }, { 8192, 13 },
	{ 16384, 14 }, { 32768, 15 }, { 65536, 16 }
}; // use the gcc compiler to handle this

vector<int> arrtovec( const int *arr )
{
	int i;
	vector<int> v( 4 );
	for( i = 0; i < 4; i++ )
		v[i] = arr[i];
	return v;
}

btoi::btoi( const Board arr )
{
	int i;
	b = 0;
	for( i = 3; i >= 0; i-- )
	{
		b <<= 16;
		b |= rowtoint( arrtovec( arr.board[i] ) );
	}
}

btoi::btoi( const btoi &other )
{
	gameOver = other.gameOver;
	b = other.getBoard( );
}

bool btoi::isGameOver( )
{
	unsigned long long cpy = b;
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
	unsigned short r, c;
	unsigned long long newr, newc;
	unsigned long long cpy = 0;
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

unsigned long long btoi::getBoard( ) const
{
	return b;
}

unsigned short btoi::getRow( const int &row ) const
{
	return b >> ( 16 * row );
}

unsigned short btoi::getCol( const int &col ) const
{
	int i;
	unsigned short colVal = 0;
	unsigned long long temp = b >> ( 4 * col );
	for( i = 0; i < 4; i++ )
		colVal |= ( ( temp >> ( 16 * i ) ) & 15 ) << ( 4 * i );
	return colVal;
}

unsigned short btoi::rowtoint( const vector<int> &row ) const
{
	int i;
	unsigned short r = 0;
	for( i = 3; i >= 0; i-- )
	{
		r <<= 4;
		if( row[i] )
			r |= ( int ) log2( row[i] );
	}
	return r;
}

void btoi::placeCol( unsigned long long &bc, unsigned short colVal, const int &col ) const
{
	int i;
	for( i = 0; i < 4; i++ )
		bc |= ( ( ( unsigned long long ) colVal >> ( 4 * i ) ) & 15 ) << ( 16 * i + 4 * col );
}

void btoi::setVal( const int i, const int j, const int val )
{
	b &= ~( 15LL << ( 16 * i + 4 * j ) );
	b |= ( ( unsigned long long ) log2Val[ val ] ) << ( 16 * i + 4 * j );
}

int btoi::getVal( const int i, const int j ) const
{
	int val = 1 << ( ( b >> ( 16 * i + 4 * j ) ) & 15 );
	if( val == 1 )
		return 0;
	return val;
}
