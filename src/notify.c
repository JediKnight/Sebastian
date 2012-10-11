#include <curses.h>
#include <stdlib.h>

#include "notify.h"

void newBuffer()
{
  if(initscr() == NULL)
    {
      fprintf(stderr, "initscr failure\n");
      exit(EXIT_FAILURE);
    }
}

void endBuffer(int status)
{
  if(status == WAIT)
    getch();

  endwin();
}

void notify(char *val)
{
  newBuffer();
  printw("%s", val);
  endBuffer(WAIT);
}
