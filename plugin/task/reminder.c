#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

enum { YEAR = 0, MONTH, DAY, HOUR, MINUTE, SECOND };

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
      break;

    case DAY:
      break;

    case HOUR:
      break;

    case MINUTE:
      break;

    case SECOND:
      break;

    default:
      fprintf(stderr, "type");
      exit(EXIT_FAILURE);
    }

  system("stty raw");
  for(i = l_lmt -1; i >= 0;)
    {
      c = fgetc(stdin);
      if('0' <= c && '9' >= c)
	{
/* 	  if(c_lmt > c || v_lmt >= v) */
/* 	    { */
/* 	      printf("%c", c); */
/* 	    } */
/* 	  else */
/* 	    { */
/* 	      printf("0%c", c); */
/* 	    } */
	  printf("%c", c);
	  v += (c - '0') * (int)pow((double)10, (double)i);
	  i--;
	}
    }
  system("stty -raw");
  return v;
}

void signalHander(int signo)
{
  fprintf(stdout, "hogehogedayo");
}

void setSignal(int type)
{
  if(signal(type, signalHander) == SIG_ERR)
    {
      perror("signal");
      exit(EXIT_FAILURE);
    }
}

void initDate()
{
  time_t tm_n, tm_c;
  struct tm stm;
  int tm_wait;

  setSignal(SIGALRM);
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

  if((tm_wait = difftime(tm_n, tm_c)) <= 0)
    {
      fprintf(stdout, "指定時間が現在時刻よりなんやかんかや");
      exit(1);
    }

  alarm(tm_wait);
}

void mainLoop()
{
  for(;;)
    sleep(1);

  exit(EXIT_SUCCESS);
}

int main()
{
  pid_t pid;

  if((pid = fork()) > 0)
    {
      perror("fork");
      exit(EXIT_FAILURE);
    }

  else if(pid == 0)
    {
      initDate();
      mainLoop();
    }

  else
    {
      exit(EXIT_SUCCESS);
    }

  return 0;
}
