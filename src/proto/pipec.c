#include <stdlib.h>
#include <unistd.h>
#include "pipec.h"

void pipegen()
{
  if(pipe(fds) < 0)
    {
      perror("pipe()");
      exit(EXIT_FAILURE);
    }
}
