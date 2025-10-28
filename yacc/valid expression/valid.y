%{
#include<stdio.h>
#include<stdlib.h>

int yylex();
void yyerror(const char *s);
%}

%token NUMBER IDENTIFIER
%left '+' '-'
%left '*' '/' '%'
%nonassoc UMINUS

%%

input:
    expr { printf("Valid\n"); }
    ;

expr:
      expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | expr '%' expr
    | '(' expr ')'
    | '-' expr %prec UMINUS
    | NUMBER
    | IDENTIFIER
    ;

%%

void yyerror(const char *s) {
    printf("INVALID EXPRESSION\n");
}

void main(){
    printf("enter expression :");
    yyparse();
}
