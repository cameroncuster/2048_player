#ifndef _BTOI_H_
#define _BTOI_H_
#include <vector>
#include "board.h"


constexpr const ValidMove moves[4] = { LEFT, DOWN, RIGHT, UP };

using namespace std;

class btoi
{
	long long b;

	public:
	btoi( const Board arr, vector<vector<short>> sTable );
	long long getBoard( ) const;
	bool isGameOver( );
	bool checkMove( ValidMove move );

	short rowtoint( const vector<int> &row ) const;

	short getRow( const int &row ) const;
	short getCol( const int &col ) const;

	// transposition table
	vector<vector<short>> table;

	private:
	void placeCol( long long &bc, short colVal, const int &col ) const;
	void placeRow( long long &bc, const short &rowVal, int row ) const;
};
#endif
