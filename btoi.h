#ifndef _BTOI_H_
#define _BTOI_H_
#include <vector>
#include <unordered_map>
#include <cassert>
#include "board.h"

extern vector<vector<short>> table;

constexpr const ValidMove moves[4] = { LEFT, DOWN, RIGHT, UP };

using namespace std;

class btoi
{
	long long b;

	public:
	btoi( const Board arr );
	btoi( const btoi &other );

	long long getBoard( ) const;
	bool isGameOver( );
	bool checkMove( ValidMove move );

	short rowtoint( const vector<int> &row ) const;

	short getRow( const int &row ) const;
	short getCol( const int &col ) const;

	// set or get i, j
	void setVal( const int i, const int j, const int val );
	int getVal( const int i, const int j ) const;

	private:
	void placeCol( long long &bc, short colVal, const int &col ) const;
	void placeRow( long long &bc, const short &rowVal, int row ) const;
};
#endif
