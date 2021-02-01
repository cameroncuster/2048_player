#include "game.h"

/***************************************************************************\\**
 * @file game.cpp
 *
 * @brief Constructor
 *
 * @param[in] p - A player object which will make moves during the game
 ******************************************************************************/
Game::Game(Player *p) : player(p), gameOver(false), score(0)
{
#ifdef GRAPHICS
   // if the game is to be played with animations, load the images
   loadImages(); 
#endif
}

/***************************************************************************\\**
 * @brief Destructor
 ******************************************************************************/
Game::~Game()
{
   delete player;
}

/***************************************************************************\\**
 * @brief makeMove asks the player object to make a move based on current board
 *
 * @return true iff the player has made a valid move
 ******************************************************************************/
bool Game::makeMove()
{
   // Ask the player object for a move
   ValidMove playerMove = player->makeMove(board);

   // Attempt to make the move on the current board
   bool retVal = board.makeMove(playerMove);

   // Update the current score
   score = board.getScore();

   // If the player did not make a move the game is over 
   if (playerMove == NONE) gameIsOver();

   // If there are no valid moves remaining, the game is over
   gameOver = isGameOver();

   return retVal;
}

void Game::gameIsOver() { gameOver = true; }

/***************************************************************************\\**
 * @brief isGameOver checks if any valid moves remain
 *
 * @return true iff there are no valid moves remaining 
 ******************************************************************************/
bool Game::isGameOver()
{
   if (gameOver) return true;
   gameOver = true;
   for (ValidMove move : {DOWN, LEFT, RIGHT, UP})
   {
       Board temp(board);
       if (temp.checkMove(move))
          gameOver = false;
   }
   return gameOver;
}

/***************************************************************************\\**
 * @brief getBoard
 *
 * @return a copy of the current board
 ******************************************************************************/
Board Game::getBoard()
{
   Board tmp(board);
   return tmp;
}

int Game::getScore() { return score ; }

/***************************************************************************\\**
 * @brief loadImages loads the images of the board and tiles
 *
 * @par Description
 *    If we are displaying the game play then load the bmps that represent
 *    the board and tiles
 ******************************************************************************/
void Game::loadImages()
{
#ifdef GRAPHICS
   // Load the tile and board images
   stringstream ss;
   unsigned char *image;
   int width;
   int height;

   for (int i = 2 ; i < 32768 ; i *= 2)
   {
      ss << "Images/" << i << "Tile.bmp";
      loadBMP(ss.str().c_str(), width, height, image);
      GLuint tex;
      bindImageToTexture(&tex, width, height, image);
      delete []image;
      tiles[i] = tex;
      ss.str("");
   }

   ss << "Images/Board.bmp";
   loadBMP(ss.str().c_str(), width, height, image);
   bindImageToTexture(&gameBoard, width, height, image);
   delete []image;
#endif
}

/***************************************************************************\\**
 * @brief draw the gameboard
 *
 * @par Description
 *    If we are displaying the game play then draw the game board after each
 *    turn
 ******************************************************************************/
void Game::draw()
{
#ifdef GRAPHICS
   // if the game is being played in animation mode, draw the board after each
   // move
   drawTexture(gameBoard, 0, 0, 500, 500);
   for (int i = 0 ; i < 4 ; i++)
      for (int j = 0 ; j < 4 ; j++)
      {
         int val = board.board[j][i];
         if (val != 0)
         {
            int x1 = 14 + (i*122);
            int y1 = 500 - (j*122) - 122;

            drawTexture(tiles[val], x1, y1, x1+108, y1+108);
         }
      }
   glFlush();
#else
   board.printBoard();
#endif
}
