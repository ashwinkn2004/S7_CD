%{
#include<stdio.h>    
int lines = 0, words = 0, charc = 0;
%}

%%
[a-zA-Z0-9]+ {charc += yyleng; words++;}
\n {lines++;}
. ; 
%%

void main(){
    printf("Enter the input :");
    yylex();
    printf("Words = %d\nLines = %d\nCharacter = %d\n", words, lines, charc);
}

int yywrap(void){
    return 1;
}