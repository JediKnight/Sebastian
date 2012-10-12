#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include "forkc.h"
#include "pipec.h"

enum { IN = 0, OUT };

void childp()
{
  char mesg[] = "hello parent", buf[32];
  memset(buf, '\0', sizeof(buf) / sizeof(buf[0]));
  if(read(fds[IN], buf, sizeof(buf)) < 0)
    {  
      perror("read()");
      exit(EXIT_FAILURE);
    }
  printf("%s, child process received\n", buf);

  if(write(fds[OUT], mesg, sizeof(mesg)/ sizeof(mesg[0])) < 0)
    {
      perror("write()");
      exit(EXIT_FAILURE);
    }
  
  close(fds[IN]);
  close(fds[OUT]);
  exit(EXIT_SUCCESS);
}

void parentp()
{
  char mesg[] = "hello child", buf[32];
  int status;
  memset(buf, '\0', sizeof(buf) / sizeof(buf[0]));
  if(write(fds[OUT], mesg, sizeof(mesg) / sizeof(mesg[0])) < 0)
    {
      perror("write()");
      exit(EXIT_FAILURE);
    }

  sleep(1);

  if(read(fds[IN], buf, sizeof(buf)) < 0)
    {
      perror("read()");
      exit(EXIT_FAILURE);
    }
  printf("%s, parent process received\n", buf);

  wait(&status);

  close(fds[IN]);
  close(fds[OUT]);
}

int main(int argc, char** argv)
{
  pipegen();
  return 0;
}
