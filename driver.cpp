#include <iostream>
#include <chrono>
#include <vector>
#include "game.h"
#include "player.h"

using namespace std;
using namespace std::chrono;

int main()
{
   // declare some variables to measure elapsed time between moves
   vector<duration<double>> turnTimes;
   time_point<system_clock> start, end;

   // Instantiate a player
   Player *player = new Player();
   // Use dependency injection to create a game object
   Game *game = new Game(player);

   // Loop over the game object while the game is ongoing
   while (!game->isGameOver())
   {
      start = system_clock::now();
      game->makeMove();
      end = system_clock::now();
      turnTimes.push_back(end-start);
   }
   cout << "Final Score: " << game->getScore() << endl;
   cout << "Max Tile   : " << game->getBoard().maxVal() << endl;

   double sum = 0.0;
   for(duration<double> d : turnTimes)
      sum += d.count();

   cout << "Average turn time: " << sum/turnTimes.size() << endl;
   return 0;
}
