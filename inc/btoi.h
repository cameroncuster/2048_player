#ifndef _BTOI_H_
#define _BTOI_H_
#include <vector>
#include <unordered_map>
#include <cassert>
#include "board.h"

extern vector<vector<unsigned short>> table;

extern vector<vector<double>> scoreTable;

constexpr const ValidMove moves[4] = { LEFT, DOWN, RIGHT, UP };

using namespace std;

class btoi
{
	unsigned long long b;

	public:
	btoi( const Board arr );
	btoi( const btoi &other );

	unsigned long long getBoard( ) const;
	bool isGameOver( );
	bool checkMove( ValidMove move );

	unsigned short rowtoint( const vector<int> &row ) const;

	unsigned short getRow( const int &row ) const;
	unsigned short getCol( const int &col ) const;

	void setVal( const int i, const int j, const int val );
	int getVal( const int i, const int j ) const;

	private:
	void placeCol( unsigned long long &bc, unsigned short colVal, const int &col ) const;
	void placeRow( unsigned long long &bc, const unsigned short &rowVal, int row ) const;
};
#endif
