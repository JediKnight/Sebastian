%{
#include <stdio.h>
#include "main.h"
enum { _ERROR = -1, _QUIT, _CALC };
%}

QUIT "quit"
CALC "calc"
ERROR .

%%
{QUIT} { return _QUIT; }
{CALC} { calculator(); return _CALC; }
{ERROR} {return _ERROR; }
%%

int yywrap() { return 1; }
int yyerror(char *message) { printf("ERROR: %s\n", message); return -1; }
int wakeupSebastian()
{
  int t;

  while((t = yylex()) != 0)
    {
      switch(t)
        {
	case _CALC:
	  printf("calc> ");
	  break;
	  
	case _QUIT:
	  printf("Goodbye!!");
	  break;

	default:
	  return -1;
	  break;
	}
    }

  return 0;    
}
