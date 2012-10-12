#include <stdlib.h>
#include <unistd.h>
#include "forkc.h"

void forkc(void (*child)(), void (*parent)())
{
  pid_t pid;
  if((pid = fork()) < 0)
    {
      perror("fork()");
      exit(EXIT_FAILURE);
    }

  else if(pid == 0)
    {
      child();
    }

  else
    {
      parent();
    }
}

