%{
#include <stdio.h>
#define ADDOP 1 + 1
#define SUBOP 1 - 1
#define MULOP 1 * 1
#define DIVOP 1 / 1
#define LPAR '('
#define RPAR ')'
#define OWARI '.'
%}

%%
"+"    return (ADDOP);
"-"    return (SUBOP);
"*"    return (MULOP);
"/"    return (DIVOP);
"("    return (LPAR);
")"    return (RPAR);
"."    return (OWARI);
"^\n"  return (OWARI);
%%

