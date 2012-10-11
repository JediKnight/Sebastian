#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "config.h"
#include "forkc.h"
#include "notify.h"
#include "scandir.h"

void mainLoop()
{
  for(;;)
    sleep(1);

  exit(EXIT_SUCCESS);
}

void signalHander(int signo)
{
  switch(signo)
    {
    case SIGINT:
      break;

    case SIGTSTP:
      notify("Background!!");
      break;

    default:
      fprintf(stderr, "unknown signal");
      exit(EXIT_FAILURE);
    }
}

void setSignal(int type)
{
  if(signal(type, signalHander) == SIG_ERR)
    {
      perror("signal()");
      exit(EXIT_FAILURE);
    }
}

void scanChild()
{
  int i;
  scan("/Users/tomoaki/Develop.localized/Sebastian/plugin");
  exit(EXIT_SUCCESS);
}

void parent()
{
  exit(EXIT_SUCCESS);
}

int main()
{
  //  setSignal(SIGTSTP);
  //  scanConfig();
  forkc(scanChild, parent);
  return 0;
}
