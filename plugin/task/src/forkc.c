#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "forkc.h"

void forkc(void (*child)(), int wflg)
{
  pid_t pid, pidch;
  int status;
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
      if(wflg)
	{
	  if((pidch = wait(&status)) < 0)
	    {
	      perror("wait()");
	      exit(EXIT_FAILURE);
	    }

	  if (WIFEXITED(status))
	    {
	      printf("親プロセス : 子プロセスは終了ステータス%dで正常終了しました\n", WEXITSTATUS(status));
	    }
	  
	  else if (WIFSIGNALED(status))
	    {
	      printf("親プロセス : 子プロセスはシグナル番号%dで終了しました\n", WTERMSIG(status));
	    }
	  
	  else
	    {
	      exit(EXIT_SUCCESS);
	    }
	}

      else
	{
	  exit(EXIT_SUCCESS);
	}
    }
}
