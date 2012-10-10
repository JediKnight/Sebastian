#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "signalc.h"

void signalHander(int signo)
{
  switch(signo)
    {
    case SIGALRM:
      fprintf(stdout, "%s", "hogehoge");
      exit(EXIT_SUCCESS);
    }
}

void setSignal(int type)
{
  if(signal(type, signalHander) == SIG_ERR)
    {
      perror("signal");
      exit(EXIT_FAILURE);
    }
}
