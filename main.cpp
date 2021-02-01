#include <iostream>
#include <GL/glut.h>
#include "util.h"

using namespace std;

/***************************************************************************//**
 * Standard startup code.  The first command line argument indicates the time
 * requested per 'ticks' of the timer.  Defaults to 2000ms (2 sec)
 ******************************************************************************/
int main(int argc, char *argv[])
{
   glutInit(&argc, argv);
   int msec = 2000;
   if (argc > 1) msec = atoi(argv[1]);
   initOpenGL(msec);

   glutMainLoop();
   return 0;
}

/**************************************************************************//**
 * Standard OpenGL init plus the delay between ticks (msec)
 *****************************************************************************/
void initOpenGL(int msec)
{
   char name[] = "2048 Solver";
   glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
   
   glutInitWindowSize(510, 510);

   glutInitWindowPosition(50,50);      // initial window  position
   glutCreateWindow(name);      // window title

   glClearColor(0,0,0,0);              // use black for glClear command
   glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
   glEnable(GL_BLEND);
   glMatrixMode(GL_PROJECTION);

   glutDisplayFunc(display);           // how to redisplay window
   glutReshapeFunc(reshape);           // how to resize window
   glutKeyboardFunc(keyboard);         // how to handle a key press
   glutTimerFunc(msec, ticktock, msec);
}

