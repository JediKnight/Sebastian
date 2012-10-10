#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
  pid_t pid = 0;
  int status;
  char buf[1024];

  pid = fork();
  if(pid < 0)
    {
      perror("fork error");
      exit(1);
    }

  if(pid == 0)
    {
      execvp("ls", argv);
      perror("/bin/cat");
      exit(1);
    }

  else
    {
      waitpid(pid, &status, 0);
      printf("chld(PID=%d) finished!\n", pid);
      
      if(WIFEXITED(status))
	{
	  printf("exit, status=%d\n", WEXITSTATUS(status));
	}
      
      else if(WIFSIGNALED(status))
	{
	  printf("signal, sig=%d\n", WTERMSIG(status));
	}
      
      else
	{
	  printf("abnomal exit\n");
	}
      
      exit(0);
    }

  return 0;
}
