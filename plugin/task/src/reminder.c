#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "reminder.h"

enum { YEAR = 0, MONTH, DAY, HOUR, MINUTE, SECOND, ON, OFF };

#define MSGSIZ 1024
int alrm;
char mesg[MSGSIZ];

int inputLimit(int type)
{
  int c, i, l_lmt = 2, v_lmt = 10, v = 0;
  char c_lmt = '1';

  switch(type)
    {
    case YEAR:
      l_lmt = 4;
      c_lmt = '9';
      v_lmt = 2000;
      break;

    case MONTH:
    case DAY:
    case HOUR:
    case MINUTE:
    case SECOND:
      break;

    default:
      fprintf(stderr, "type");
      exit(EXIT_FAILURE);
    }

  system("stty raw");
  system("stty -echo");

  for(i = l_lmt -1; i >= 0;)
    {
      c = fgetc(stdin);
      if('0' <= c && '9' >= c)
	{
	  printf("%c", c);
	  v += (c - '0') * (int)pow((double)10, (double)i);
	  i--;
	}
      
      else if('q' == c)
	{
	  exit(EXIT_FAILURE);
	}

      else if('/' == c || ' ' == c || ':' == c)
	{
	  v /= 10;
	  break;
	}
    }

  system("stty echo");
  system("stty -raw");
  return v;
}

void initDate()
{
  time_t tm_n, tm_c;
  struct tm stm;
  int w;

  stm.tm_year = inputLimit(YEAR) - 1900;
  printf("/");
  stm.tm_mon  = inputLimit(MONTH) - 1;
  printf("/");
  stm.tm_mday = inputLimit(DAY);
  printf(" ");
  stm.tm_hour = inputLimit(HOUR);
  printf(":");
  stm.tm_min  = inputLimit(MINUTE);
  printf(":");
  stm.tm_sec  = inputLimit(SECOND);
  puts("");

  tm_n = mktime(&stm);
  time(&tm_c);

  if((w = difftime(tm_n, tm_c)) <= 0)
    {
      fprintf(stderr, "指定時間が現在時刻よりなんやかんかや:%d\n", w);
      exit(EXIT_FAILURE);
    }

  fprintf(stdout, "現在時刻：%s", ctime(&tm_c));
  fprintf(stdout, "指定時刻：%s", ctime(&tm_n));
  fprintf(stdout, "%d秒後に実行", w);
  alrm = w;
}

void initMesg()
{
  memset(mesg, '\0', MSGSIZ);
  
}

void init()
{
  initDate();
  initMesg();
}

void child()
{
  alarm(alrm);
  for(;;)
    sleep(1);

  exit(EXIT_SUCCESS);
}

int main()
{
  pid_t pid;
  int status;

  setSignal(SIGALRM);
  init();
  forkc(child, 0);
  return 0;
}
