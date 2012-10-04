#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/param.h>


#include "sebastian.h"

//TODO: sebascan

int main(int argc, char **argv, char **envp)
{
  pid_t pid;
  char *ext;
  char path[10];

  if(getcwd(path, sizeof(path) / sizeof(path)) == NULL)
    {
      perror("getpwd:");
      return -1;
    }

  if((pid = fork()) < 0)
    {
      perror("fork:");
      return -1;
    }

  printf("%s\n", path);
  
  execlp("php", "php", "test.php", NULL);
  exit(-1);

  return 0;
}
