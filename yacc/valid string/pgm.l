%{
#include "y.tab.h"
#include <stdio.h>
void yyerror(const char *);
%}

%%
a       { return A; }
b       { return B; }
[\n] ;  {return 0;}           /* ignore spaces and newline */
.       { yyerror("Invalid character"); }
%%

int yywrap() { return 1; }
