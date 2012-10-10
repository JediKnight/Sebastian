%{
#include <stdio.h>
enum { ZERO = 0, COLON };
%}

%%
":"  { return COLON; }
%%

int scan()
{
return yylex();
}
