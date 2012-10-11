#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "main.h"

enum { YEAR = 0, MONTH, DAY, HOUR, MINUTE, SECOND, ON, OFF };

int alrm;
char mesg[MSGSIZ];

/* 関数名クソすぎる */
int inputLimit(int type)
{
  /* 
   * l_lmtは文字数制限 
   * 年の入力以外は２文字制限だからデフォルトで２
   */
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

  system("stty raw");		/* terminfoとかをみよう */
  system("stty -echo");

  for(i = l_lmt -1; i >= 0;)
    {
      c = fgetc(stdin);
      if('0' <= c && '9' >= c)
	{
	  printf("%c", c);
	  /* 
	   * 入力された数字を10のi乗して代入していくよ
	   * c から '0'を引いてるのはアスキーコードの0が48だから48引いてintの0にするためす
	   */
	  v += (c - '0') * (int)pow((double)10, (double)i);
	  i--;
	}
      
      /* qが押されたら終了するだ */
      else if('q' == c)
	{
	  exit(EXIT_FAILURE);
	}

      /* '/' ' ' ':' が押されたら10分の1にしてbreakよ */
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

  /*
   * tm構造体に時間を代入していくよ
   * yearが-1900なのは1900年からの経過時間だからなんだ
   * monが- 1なのは0 ~ 11までだからなんだよ
   */
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

  tm_n = mktime(&stm);          /* tm構造体をtime_t型に変換する */
  time(&tm_c);			/* 現在時間を取得です */

  /*
   * difftimeで第一引数と第二引数を比較します
   * 戻り値が第一引数から第二引数を引いた数なので、-の値だったらそもそも設定自体が過去だから失敗処理でexit
   */
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
  /* mesgを'\0'で埋める */
  memset(mesg, '\0', MSGSIZ);
  /* 処理かけ */
}

/*
 * 子プロセスの処理を書こう
 */
void child()
{
  alarm(alrm);			/* グローバル変数のalrmでalarmシグナルを発動させよう */
  for(;;)			/* 時間までkillされたらこまるからsleep 1で無限ループ */
    sleep(1);

  exit(EXIT_SUCCESS);
}

/* 
 * シグナル受信したら実行される
 * signoでシグナルナンバーが取れるので、こいつで処理分岐
 * 今回はアラームしかないけどな
 */
void signalHander(int signo)
{
  /* みたらわかるべ */
  switch(signo)
    {
    case SIGALRM:
      fprintf(stdout, "%s", "hogehoge");
      exit(EXIT_SUCCESS);
    }
}

/*
 * シグナル設定用関数
 * typeにシグナルのタイプが入るよ
 */
void setSignal(int type)
{
  /* 第二引数は関数のポインタ */
  if(signal(type, signalHander) == SIG_ERR)
    {
      perror("signal");
      exit(EXIT_FAILURE);
    }
}

int main()
{
  setSignal(SIGALRM);		/* シグナルを設定 */
  initDate();			/* アラーム時間を設定 */
  initMesg();			/* アラームの時に表示するメッセージを設定 */
  forkc(child, 0);		/* 子プロセスを起動 第二匹数0:子プロセス終了を待たずに親プロセスをkill 1:子プロセスの終了を待つ */
  return 0;
}
