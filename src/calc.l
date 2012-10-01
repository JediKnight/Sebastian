%{
#include <stdio.h>
#include <stdlib.h>
#include "calc.tab.h"
%}

NUMBER [0-9]+
SPACE  [\t ]
OP     [+-/*()]
CR     [\n]
QUIT   "quit"
OTHER  .

%%
{NUMBER} { yylval = atoi(yytext); return NUMBER; }
{OP}     { return yytext[0]; }
{CR}     { return yytext[0]; }
{SPACE}  {}
{OTHER}  { printf("Goodbye!!\n"); return -1; }
%%

