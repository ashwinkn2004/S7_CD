%{
#include <stdio.h>

int yylex();
void yyerror(const char *c);
%}

%token A B

%%
input:
      str { printf("Valid string\n"); }
    ;

str:
      A str B
    | /* empty */   /* base case */
    ;
%%

void yyerror(const char *c) {
    printf("Invalid string\n");
}

int main() {
    printf("Enter the input string: ");
    yyparse();
    return 0;
}
