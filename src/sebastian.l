%{
#include "sebastian.h"
enum { ZERO = 0, QUIT, GOOGLE, STR, NUM, REAL, ERROR };
%}
%option reentrant
%%
"quit"                              { return QUIT;   }
"google"                            { return GOOGLE; }
[_$a-zA-Z][_$0-9a-zA-Z://.]*        { return STR;    }
0|[1-9][0-9]*                       { return NUM;    }
([0-9]+"."[0-9]*|([0-9]*)"."[0-9]+) { return REAL;   }
"\n"|" "|"\t"                       {                }
"/*"[0-9a-zA-Z _$]*"*/"             {                }
.                                   { return ERROR;  }
%%
	   int yywrap(yyscan_t yyscanner)
	   {
	     return 1;
	   }

	   int yyerror(char *error)
	   {
	     printf("ERROR: %s\n", error);
	     return -1;
	   }
	   int strpar()
	   {
	     yyscan_t scanner;
	     int t;
	     char *p;
	     
	     yylex_init(&scanner);
	     while((t = yylex(scanner)) != 0)
	       {
		 switch(t)
		   {
		   case QUIT:
		     puts("Goodbye");
		     return 0;
		     break;
		     
		   case GOOGLE:
		     printf("search> %s\n", "google");
		     break;
		     
		   default:
		     p = yyget_text(scanner);
		     printf("sebastian> %s\n", p);
		     break;
		   }

		 printf("> ");
	       }
	     
	     yylex_destroy(scanner);
	     
	     return 0;
	   }
