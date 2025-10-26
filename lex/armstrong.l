%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h> 

int num = 0, len = 0, numorg = 0;
int res = 0, temp = 0;
%}

%%
[0-9]+    { num = atoi(yytext); len = yyleng; }
\n        { return 0; }
.         ;
%%

void main() {
    printf("Enter the input: ");
    yylex();   

    numorg = num;

    while (num != 0) {
        temp = num % 10;
        res += pow(temp, len); 
        num /= 10;
    }

    if (res == numorg) printf("Armstrong\n");
    else printf("Not\n");
}

int yywrap(void) {
    return 1;
}
