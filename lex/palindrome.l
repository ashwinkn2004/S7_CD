%{
#include<stdio.h>   
#include<string.h>

char str[50];
%}

%%
[a-zA-Z]+ {strcpy(str, yytext);}
\n {return 0;}
. ;
%%

void main(){
    printf("Enter the input : ");
    yylex();

    int flag = 1;

    int len = strlen(str);
    for(int i = 0; i < len / 2; i++){
        if(str[i] != str[len-i-1]){
            flag = 0;
            break;
        }
    }

    if(flag){
        printf("Palindrome\n");
    }
    else printf("Not palindrome\n");
}

int yywrap(void){
    return 1;
}