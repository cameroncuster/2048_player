#include <iostream>
#include <ctime>
#include <random>
#include "btoi.h"

using namespace std;

vector<int> inttoRow( const unsigned short &r )
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

int main( )
{
	srand( time( NULL ) );

	int i, j, k;

	Board b;
	btoi intboard( b );
	vector<int> row;
	vector<int> newRow( 4 );

	table.resize( 2, vector<unsigned short>( 1 << 16 ) );

	cout << "BUILDING TRANSPOSITION TABLE..." << endl;

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

	cout << "TESTING..." << endl;

	// TEST
	for( k = 0; k < 1000; k++ )
	{
		for( i = 0; i < 4; i++ )
		{
			for( j = 0; j < 4; j++ )
			{
				if( rand( ) % 2 )
					b.board[i][j] = 0;
				else
					b.board[i][j] = pow( 2, rand( ) % 4 + 1 );
			}
		}
		btoi newintboard( b );
		for( ValidMove move : moves )
		{
			cout << "MOVE: " << move << endl;
			// DEBUG PRINT
			cout << "BEFORE M" << endl;
			for( int x = 0; x < 4; x++ )
			{
				for( int y = 0; y < 4; y++ )
					cout << b.board[x][y] << ' ';
				cout << endl;
			}
			cout << endl << endl << endl;

			assert( b.checkMove( move ) == newintboard.checkMove( move ) );

			// DEBUG PRINT
			cout << "AFTER M" << endl;
			for( int x = 0; x < 4; x++ )
			{
				for( int y = 0; y < 4; y++ )
					cout << b.board[x][y] << ' ';
				cout << endl;
			}
			cout << endl << endl << endl;

			for( i = 0; i < 4; i++ )
				for( j = 0; j < 4; j++ )
					assert( b.board[i][j] == newintboard.getVal( i, j ) );
		}
		cout << "TEST#: " << k << endl;
	}

	cout << "SUCCESS!" << endl;

	return 0;
}
