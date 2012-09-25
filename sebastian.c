#include "sebastian.h"


int main()
{
  char s[256];

  fgets(s, 256, stdin);
  DelReturn(s, strlen(s) - 1);

  printf("%s\n", s);
  return 0;
}
