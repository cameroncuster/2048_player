#include "event.h"

void cleanUpMemory(Game *game)
{
   delete game;
}

KeyboardEvent::KeyboardEvent(unsigned char k, int x, int y) : key(k), x(x), y(y) {}

void KeyboardEvent::doAction(Game *game)
{
   if (key == ESCAPE_KEY)
   {
      cleanUpMemory(game);
      glutLeaveMainLoop();
   }
}

void DisplayEvent::doAction(Game *game)
{
   game->draw();
}

ReshapeEvent::ReshapeEvent(int w, int h) : w(w), h(h) {}

void TickTockEvent::doAction(Game *game)
{
   game->makeMove();
   glutPostRedisplay();
}
