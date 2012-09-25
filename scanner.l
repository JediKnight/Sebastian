%{
#include <math.h>
#include "scanner.h"
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
  ERROR
};
%}
%option reentrant
%%
[_$a-zA-Z][_$0-9a-zA-Z]*            { return ID; }
0|[1-9][0-9]*                       { return NUM; }
([0-9]+"."[0-9]*|([0-9]*)"."[0-9]+) { return REAL; }
"+"    { return ADDOP; }
"-"    { return SUBOP; }
"*"    { return MULOP; }
"/"    { return DIVOP; }
"("    { return LPAR;  }
")"    { return RPAR;  }
"\n"|" "|"\t"           {}
"/*"[0-9a-zA-Z _$]*"*/" {}
.      { return ERROR; }
%%
int yywrap(yyscan_t yyscanner) { return 1; }

int strpar()
{
  yyscan_t scanner;
  int t;

  yylex_init(&scanner);
  while((t = yylex(scanner)) != 0)
    {
      printf("%s\n", yyget_text(scanner));
    }

  yylex_destroy(scanner);

  return 0;
}
