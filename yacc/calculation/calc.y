%{
#include<stdio.h>  

int yylex();
void yyerror(const char *c); 
%}

%token NUMBER
%left '+''-'
%left '*''/''%'
%nonassoc UMINUS

%%
input: expr {printf("RESULT = %d\n", $$);}
expr: expr'+'expr {$$ = $1 + $3;}|
      expr'-'expr {$$ = $1 - $3;}|
      expr'*'expr {$$ = $1 * $3;}|
      expr'/'expr {
        if($3 == 0){
            yyerror("Division By Zero");
        }
        else{
            $$ = $1 / $3;
        }
      }|
      expr'%'expr {$$ = $1 % $3;}|
      '('expr')' {$$ = $2;}|
      '-' expr %prec UMINUS {$$ = -$2;}|
      NUMBER {$$ = $1;}
%%

void yyerror(const char *c){
    printf("%s\n", c);
}

void main(){
    printf("Enter the expression : ");
    yyparse();
}