%{
#include "sebastian.h"
enum {
  ZERO = 0,
  ID,
  NUM,
  REAL,
  ADDOP,
  SUBOP,
  MULOP,
  DIVOP,
  LPAR,
  RPAR,
  ASK,
  QUIT,
  ERROR
};
%}

%option reentrant
%%
"ask"                               { return ASK;   }
"quit"                              { return QUIT;  }
[_$a-zA-Z][_$0-9a-zA-Z]*            { return ID;    }
0|[1-9][0-9]*                       { return NUM;   }
([0-9]+"."[0-9]*|([0-9]*)"."[0-9]+) { return REAL;  }
"+"                                 { return ADDOP; }
"-"                                 { return SUBOP; }
"*"                                 { return MULOP; }
"/"                                 { return DIVOP; }
"("                                 { return LPAR;  }
")"                                 { return RPAR;  }
"\n"|" "|"\t"                       {               }
"/*"[0-9a-zA-Z _$]*"*/"             {               }
.                                   { return ERROR; }
%%

int yywrap(yyscan_t yyscanner) { return 1; }

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
	case ASK:
	  printf("ｔａｎｏｍａｒｅｍａｓｉｔａ");
	  break;

	case QUIT:
	  puts("Goodbye");
	  return 0;
	  break;

	default:
	  p = yyget_text(scanner);
	  printf("sebastian> %s\n", p);
	  printf("> ");
	  break;
	}
    }

  yylex_destroy(scanner);

  return 0;
}
