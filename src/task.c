#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TIMESTRING strlen("YYYY/mm/dd HH:MM:SS") + 1
#define TSTRNUM strlen("YYYYmmddHHMMSS")
#define addNull(s, n) if(s[n -1] == '\n') s[n -1] = '\0'
#define delRubbish(v, s)						\
  for(;;) {								\
    char *p = strstr(v, s);						\
    if(p == NULL) break;						\
    memmove(v + strlen(v) - strlen(p), p + strlen(s), strlen(p));	\
  }

#define chnum(s) (strlen(s) == TSTRNUM) ? 0 : -1

char mesg[1024];

void signalHandler(int signo)
{
  switch(signo)
    {
    case SIGALRM:
      fprintf(stdout, "\ntask>%s\n", mesg);
      exit(EXIT_SUCCESS);
      
    default:
      exit(EXIT_FAILURE);
    }
}

void setSignal(int sigtype)
{
    if(signal(sigtype, signalHandler) == SIG_ERR)
    {
      perror("signal");
      exit(EXIT_FAILURE);
    }
}

struct tm timegen(char *time)
{
  struct tm stm;
  stm.tm_year = atoi(strtok(time, "/")) - 1900;
  stm.tm_mon  = atoi(strtok(NULL, "/")) - 1;
  stm.tm_mday = atoi(strtok(NULL, " "));
  stm.tm_hour = atoi(strtok(NULL, ":"));
  stm.tm_min  = atoi(strtok(NULL, ":"));
  stm.tm_sec  = atoi(strtok(NULL, " "));
  return stm;
}

void getstdin(char *val, int size)
{
  if(fgets(c, TIMESTRING, stdin) != NULL)
    {
      addNull(c, size);
    }
}

void mainLoop()
{
  time_t tm_t, tm_c;
  struct tm st_tm;
  char tmstr[TIMESTRING], *p;
  int w;

 DATE:
  puts("YYYY/mm/dd HH:MM:SS 形式でお知らせして欲しい時間を入力");
  printf("> ");
  
  else
    {
      puts("入力形式が不正\n");
      exit(EXIT_FAILURE);
      goto DATE;
    }
  
  puts("メッセージを入力");
  printf("> ");
  if(fgets(mesg, sizeof(mesg) / sizeof(mesg[0]), stdin) != NULL)
    {
      addNull(mesg, sizeof(mesg) / sizeof(mesg[0]));
    }

  st_tm = timegen(tmstr);
  tm_t = mktime(&st_tm);
  time(&tm_c);

  if((w = difftime(tm_t, tm_c)) <= 0)
    {
      fprintf(stdout, "指定時間が現在時刻よりなんやかんかや");
      exit(1);
    }

  alarm(w);

  for(;;)
    {
      sleep(1);
    }

  exit(EXIT_SUCCESS);
}

void daemonize()
{
  pid_t pid;
  int status;

  if((pid = fork()) < 0)
    {
      perror("fork");
      exit(EXIT_FAILURE);
    }

  else if(pid == 0)
    {
      puts("mainLoop");
      mainLoop();
    }

  else
    {
      exit(EXIT_SUCCESS);
    }
}

int main(int argc, char **argv, char **evnp)
{
  setSignal(SIGALRM);
  daemonize();
  return 0;
}
