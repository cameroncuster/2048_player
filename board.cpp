#include "board.h"

/***************************************************************************\\**
 * @brief Create a new board initialized with two random tiles
 ******************************************************************************/
Board::Board() : gameOver(false), score(0), maxCellVal(2)
{
   // Pick a seed for the random number generator
   struct timespec ts;
   clock_gettime(CLOCK_MONOTONIC, &ts);
   srand((time_t)ts.tv_nsec);

   for (int i = 0 ; i < 4 ; i++)
      for (int j = 0 ; j < 4 ; j++)
         board[i][j] = 0;

   // Add two tiles to the gameboard
   addValue();
   addValue();
}

/***************************************************************************\\**
 * @brief Create a new board and copy the data from another board
 *
 * @param[in] b - The board to copy when constructing the new board
 ******************************************************************************/
Board::Board(const Board& b)
{
   for (int i = 0 ; i < 4 ; i++)
      for (int j = 0 ; j < 4 ; j++)
         board[i][j] = b.board[i][j];

   score = b.score;
   maxCellVal = b.maxVal();
   gameOver = b.gameOver;
}

int Board::maxVal() const { return maxCellVal; }

// Accessor for the state of the game
bool Board::isGameOver() { return gameOver ; }

// Add a tile to the board.
//
// 1.  Locate the empty grid cells
// 2.  If no empty cell is found, set gameOver = true and return false
// 3.  If there are empty cells, pick one at random.
// 4.  Set the cell value at 2 or 4 at a ratio of 9:1
bool Board::addValue()
{
   vector<int> emptyCells;
   for (int i = 0 ; i < 4 ; i++)
      for (int j = 0 ; j < 4 ; j++)
         if (!board[i][j])
             emptyCells.push_back(i * 4 + j);

   // If we found no empty cells, we can't place a new tile
   if (emptyCells.size() == 0) return false;

   // Pick a random empty cell
   int randCell = emptyCells[rand() % emptyCells.size()];

   // Set the random empty cell to either 2 or 4 at a 9:1 ratio
   board[randCell / 4][randCell % 4] = (rand() % 100 > 90) ? 4 : 2;

   return true;
}

int Board::getScore() const { return score ; }

/**************************************************************************\\**
 * @brief Output an ascii version of the board to stdout
 *
 * @par Description
 *    Print to standard output the board
 ******************************************************************************/
void Board::printBoard() const
{
   cout << "------------------------------\n";
   for (int i = 0 ; i < 4 ; i++)
   {
      for (int j = 0 ; j < 4 ; j++)
          cout << setw(5) << board[i][j];
      cout << endl;
   }
}

/**************************************************************************\\**
 * @brief Attempt to make a move
 *
 * @par Description
 *    Instruct the board to make a valid move.  If the requested move results
 * in a board change (i.e. tiles move or are combined) then the result returned
 * is true, the tiles move and combine as per the rules, and a new tile is
 * randomly placed on the board
 *
 * @param[in] - move : A ValidMove {UP, DOWN, LEFT, RIGHT, NONE}
 *
 * @return true iff the board changes during the requested move, false otherwise
 ******************************************************************************/
bool Board::makeMove(ValidMove move)
{
   Board temp(*this);
   bool retVal = false;

   if (!temp.anyValidMove()) 
      gameOver = true;
   else
   {
      retVal = checkMove(move);
 
      if (retVal) 
         addValue();
   }
   return retVal;
}

/**************************************************************************\\**
 * @brief Check to see if a move will result in a board change
 *
 * @par Description
 *    Attempt to move the tiles on the board in the requested direction.
 * If the requested move results in a board change (i.e. tiles move and/or
 * are combined) then the function returns true.  Otherwise it returns
 * false.
 *
 *    Note: If the move results in a board change then the board will be 
 *    changed on return.  This is the same as the makeMove function except
 *    a valid move does not result in a new tile being added.
 *
 * @param[in] - move : A ValidMove {UP, DOWN, LEFT, RIGHT, NONE}
 *
 * @return true iff the board changes during the requested move, false otherwise
 ******************************************************************************/
bool Board::checkMove(ValidMove move)
{
   bool retVal = false;
   switch (move)
   {
      case LEFT  : retVal = moveLeft(); break;
      case RIGHT : retVal = moveRight(); break;
      case UP    : retVal = moveUp(); break;
      case DOWN  : retVal = moveDown(); break;
      default: break;
   }
   return retVal;
}

/***************************************************************************\\**
 * @brief Attempt to slide and combine tiles moving left
 *
 * @par Description
 *    This method attempts to move and combine tiles on the board moving to
 * the left.  If a tile can move or two tiles can be combined.  The function
 * returns true.  Otherwise it returns false.
 *
 * @return true iff a tile on the board moves left or combines with another
 * tile.  False otherwise.
 ******************************************************************************/
bool Board::moveLeft()
{
   bool didMove = false;
   for (int row = 0 ; row < 4 ; row++)
   {
      vector<bool> canChange {true, true, true, true};
      for (int startCol = 1 ; startCol < 4 ; startCol++)
      {
         int col = startCol;
         while (col > 0)
         {
            if (board[row][col-1] == 0 && board[row][col] != 0)
            {
               board[row][col-1] = board[row][col];
               board[row][col] = 0;
               didMove = true;
            }
            else if (board[row][col-1] != 0 && board[row][col-1] == board[row][col] && canChange[col-1] && canChange[col])
            {
               board[row][col-1] += board[row][col];
               maxCellVal = (maxCellVal < board[row][col-1]) ? board[row][col-1] : maxCellVal;
               board[row][col] = 0;
               canChange[col-1] = false;
               score += board[row][col-1];
               didMove = true;
            }
            col--;
         }
      }
   }
   return didMove;
}

/***************************************************************************\\**
 * @brief Rotates the board 90 degress clockwise
 *
 * @par Description
 *    This method is called by the move operations to rotate the board 90
 * degrees in the clockwise direction.
 ******************************************************************************/
void Board::spin()
{
   int a[4][4];
   for(int i = 0 ; i < 4 ; i++)
      for (int j = 0 ; j < 4 ; j++)
         a[i][j] = board[i][j];

   for(int i=0; i<4; i++)
      for(int j=0; j<4; j++)
         board[i][j] = a[4-j-1][i];
}

/***************************************************************************\\**
 * @brief Attempt to slide and combine tiles moving left
 *
 * @par Description
 *    This method attempts to move and combine tiles on the board moving
 * up.  If a tile can move or two tiles can be combined.  The function
 * returns true.  Otherwise it returns false.
 *
 * @return true iff a tile on the board moves up or combines with another
 * tile.  False otherwise.
 ******************************************************************************/
bool Board::moveUp()
{
   spin();
   spin();
   spin();
   bool retVal = moveLeft();
   spin();
   return retVal;
}

/***************************************************************************\\**
 * @brief Attempt to slide and combine tiles moving down
 *
 * @par Description
 *    This method attempts to move and combine tiles on the board moving
 * down.  If a tile can move or two tiles can be combined.  The function
 * returns true.  Otherwise it returns false.
 *
 * @return true iff a tile on the board moves down or combines with another
 * tile.  False otherwise.
 ******************************************************************************/
bool Board::moveDown()
{
   spin();
   bool retVal = moveLeft();
   spin();
   spin();
   spin();
   return retVal;
}

/***************************************************************************\\**
 * @brief Attempt to slide and combine tiles moving right
 *
 * @par Description
 *    This method attempts to move and combine tiles on the board moving to
 * the right.  If a tile can move or two tiles can be combined.  The function
 * returns true.  Otherwise it returns false.
 *
 * @return true iff a tile on the board moves right or combines with another
 * tile.  False otherwise.
 ******************************************************************************/
bool Board::moveRight()
{
   spin();
   spin();
   bool retVal = moveLeft();
   spin();
   spin();
   return retVal;
}

/***************************************************************************\\**
 * @brief Check the board to see if there are any valid moves that can be made
 *
 * @par Description
 *    If there are valid moves that can be made, the function will return true
 *    else false
 *
 * @return true iff there exists a valid move on the board
 ******************************************************************************/
bool Board::anyValidMove()
{
   for (ValidMove move : {UP, DOWN, LEFT, RIGHT})
      if (checkMove(move)) return true;

   std::cout << "Ending game" << std::endl;
   return false;
}
