#include "sebastian.h"

int main()
{
  char s[256];

  puts("Hello, Sir\nWhat are your requirements?");

  while(strcmp(s, "quit"))
    {
      printf("> ");
      fgets(s, 256, stdin);
      DelReturn(s, strlen(s) - 1);
      
      if(strcmp(s, "quit") == 0)
	{
	  puts("Goodbye");
	  break;
	}
      printf("Sebastion> %s\n", s);
    }

  return 0;
}
