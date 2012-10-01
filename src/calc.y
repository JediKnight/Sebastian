%{
#include <stdio.h>
#include <string.h>

  void yyerror(const char *error)
  {
    fprintf(stderr,"ERROR: %s\n", error);
  }

  int yywrap()
  {
    return 1;
  }

  int calculator()
  {
    printf("calc> ");
    yyparse();
  }
%}

%token NUMBER

%left '+' '-'
%left '*' '/'

%%
lines
: line
| lines line
;

line
: '\n'
| ex '\n' { printf("%d\n", $1); }
;

ex
: NUMBER
| '(' ex ')' { $$ = $2; }
| ex '+' ex  { $$ = $1 + $3; }
| ex '-' ex  { $$ = $1 - $3; }
| ex '*' ex  { $$ = $1 * $3; }
| ex '/' ex  { $$ = $1 / $3; }
;
%%
