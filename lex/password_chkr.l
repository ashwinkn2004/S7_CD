%{
#include<stdio.h>

int summ = 0, flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0;
%}

%%
[a-z]+ {summ += yyleng; flag1 = 1;}
[A-Z]+ {summ += yyleng; flag2 = 1;}
[0-9]+ {summ += yyleng; flag3 = 1;}
[!@#$%^&*]+ {summ += yyleng; flag4 = 1;}
[\n] {return 0;}
. ;
%%

void main(){
    printf("Enter the input : ");
    yylex();
    if(summ <= 8 && flag1 == 1 && flag2 == 1 && flag3 == 1 && flag4 == 1){
        printf("YeS");
    }
    else printf("NO");
}

int yywrap(void){
    return 1;
}