#include <stdio.h>

void replTerm(char *c)
{
  char *p;
  if((p = strchr(c, '\n')) != NULL)
    *p = '\0';
}  

void scanConfig()
{
  char path[1024], poller[3];
  fprintf(stdout, "スキャンディレクトリ\n> ");
  fgets(path, sizeof(path) / sizeof(path[0]), stdin);
  replTerm(path);

  fprintf(stdout, "スキャン間隔(分指定,最大60分)\n> ");
  fgets(poller, sizeof(poller) / sizeof(poller[0]), stdin);
  replTerm(poller);

  fprintf(stdout, "スキャンディレクトリ：%s\n", path);
  fprintf(stdout, "スキャン間隔：%s\n", poller);
  exit(0);
}
