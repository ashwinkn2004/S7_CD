%{
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int yylex();
void yyerror(const char *c);

%}

%union{
    char *str;
}

%token <str> STRING

%%
input : STRING{
    int len = strlen($1);
    for(int i = 0; i < len/2; i++){
        if($1[i] != $1[len-i-1]){
            printf("Not");
            break;
        }
    }
    printf("Pali");
}
%%

void yyerror(const char *c){
    printf("%s\n", c);
}

void main(){
    printf("Enter the input : ");
    yyparse();
}