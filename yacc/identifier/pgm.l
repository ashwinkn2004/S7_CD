%{
#include "y.tab.h"
%}

%%
[a-zA-Z_][a-zA-Z0-9_]* { return IDENTIFIER; }
[\n] { return 0; }
. { return INVALID; }
%%

int yywrap() {
    return 1;
}
