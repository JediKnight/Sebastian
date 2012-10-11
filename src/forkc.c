#include <stdlib.h>
#include "forkc.h"

void forkc(void (*child)(), void (*parent)())
{
  pid_t pid;

  switch(pid = fork())
    {
    case -1:
      perror("fork()");
      exit(EXIT_FAILURE);

    case 0:
      child();
      break;

    default:
      parent();
    }
}
