#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

//TODO: sebascan

void mainLoop(int argc, char **argv, char **envp)
{
  while(1)
    {
      fprintf(stdout, "なんやかんや\n");
      sleep(1);
    }
}

void sigHandler(int signo)
{
  
}

int main(int argc, char **argv, char **envp)
{
  if (signal(p_signame， SigHandler) == SIG_ERR) 
    {
      printf('シグナルハンドラが設定できんぜよ\n');
      exit(1);
  }

  if(daemon(0, 0) == 0)
    {
      mainLoop(argc, argv, envp);
    }

  else
    {
      fprintf(stdout, "");
    }

  return 0;
}
