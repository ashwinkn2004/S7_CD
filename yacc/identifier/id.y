%{
#include <stdio.h>

int yylex();
void yyerror(const char *c);
%}

%token IDENTIFIER INVALID

%%
input: IDENTIFIER { printf("Valid\n"); }| 
       INVALID    { yyerror("INVALID"); };
%%

void yyerror(const char *c) {
    printf("%s\n", c);
}

int main() {
    printf("Enter the identifier: ");
    yyparse();
    return 0;
}
