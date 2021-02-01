/***************************************************************************\\**
 * @file game.h
 ******************************************************************************/
#ifndef __GAME_H
#define __GAME_H
#include <map>
#include <sstream>
#include <GL/freeglut.h>
#include "board.h"
#include "loadBMP.h"
#include "graphics.h"
#include "player.h"

/***************************************************************************\\**
 * @class Game
 ******************************************************************************/
class Game
{
   /// The player that generates moves during the game
   Player *player;
   /// The 4 x 4 gameboard
   Board board;
   /// Boolean describing whether the game is over or not
   bool gameOver;
   /// The current score for the board
   int  score;
   /// A map of the power of two tiles used to show the graphics of the game
   std::map<int, GLuint> tiles;
   /// A GLuint for the gameboard
   GLuint gameBoard;

public:
   /// Constructor
   Game(Player *);
   /// Destructor
   ~Game();
   /// Accessor to tell if the game is over
   bool isGameOver();
   /// A mutator to set the game is over flag
   void gameIsOver();
   /// An accessor to get the current score
   int  getScore();
   /// An accessor to get a copy of the gameboard
   Board getBoard();
   /// Method to output or draw the gameboard
   void draw();
   /// Method that calls the player object to make a move
   bool makeMove();

private:
   /// Method to load the bmp image files for the graphical display of the game
   void loadImages();
};
#endif
