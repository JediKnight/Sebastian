#include <ctype.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//TODO: sebascan

void mainLoop(int argc, char **argv, char **envp)
{
  int time = -1;

  while(time < 0)
    {
      puts("指定秒後にメッセージを表示してアプリは終了します。");
      puts("待機時間は秒で指定してください。");
      printf("timer> ");
      time = getchar() - '0';
      while(getchar() != '\n');
      
      if(time <= 0)
	{
	  fprintf(stderr, "getchar error");
	  return;
	}
      
      if(isdigit(time) > 0)
	{
	  fprintf(stderr, "数値で入力してください。");
	  return;
	}
    }

  sleep(time);
  fprintf(stdout, "時間だよ");
}

void sigHandler(int signo)
{
  fprintf(stdout, "signal=%d\n", signo);
}

void setSignal(int signo)
{
  if(signal(signo, sigHandler) == SIG_ERR)
    {
      puts("シグナルハンドラが設定できんぜよ");
      return;
    }
}

int main(int argc, char **argv, char **envp)
{
  int time;

  setSignal(SIGHUP);
  setSignal(SIGINT);
  setSignal(SIGKILL);
  setSignal(SIGALRM);
  setSignal(SIGTERM);

  time = getchar();
  while(getchar() != '\0');

  printf("%d\n", time);

  if(daemon(0, 1) == 0)
    {
      mainLoop(argc, argv, envp);
    }

  else
    {
      fprintf(stdout, "daemon: %d", errno);
    }

  return 0;
}
