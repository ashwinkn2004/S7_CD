%{
#include<stdio.h>   
int num = 0; 
%}

%%
[0-9]+ {num = atoi(yytext);}
\n {return 0;}
, ;
%%

void main(){
    printf("Enter the input : ");
    yylex();
    int cnt = 0;
    for(int i = 1; i < num; i++){
        if((num % i) == 0){
            cnt++;
        }
    }
    if(cnt == 1) printf("Prime\n");
    else printf("Not prime\n");
}

int yywrap(void){
    return 1;
}