%{
#include<stdio.h>    
int vowels = 0, conso = 0;
%}

%%
[aeiouAEIOU] {vowels++;}
[a-zA-Z] {conso++;}
\n {return 0;}
. ;
%%

void main(){
    printf("Enter the input ");
    yylex();
    printf("Vowels = %d",vowels);
    printf("Conco = %d", conso);
}

int yywrap(void){
    return 1;
}