%{
#include "y.tab.h"   
%}

%%
[a-zA-Z]+ {yylval.str = yytext; return STRING;}
\n {return 0;}
. ;
%%

int yywrap(){
    return 1;
}