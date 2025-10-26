#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX 10

struct tac{
    char lhs[MAX], op1[MAX], op, op2[MAX];
}t[MAX];

void main(){
    int limit = 0;
    printf("Enter the number of statements : ");
    scanf("%d", &limit);
    printf("Enter the TAC : \n");
    for(int i = 0; i < limit; i++){
        scanf("%s = %s %c %s", t[i].lhs, t[i].op1, &t[i].op, t[i].op2);
    }
    
    char reg[MAX];
    printf("\nASSEMBLY CODE : \n");
    for(int i = 0; i < limit; i++){
        sprintf(reg, "R%d", i);
        if(t[i].op == '_'){
            printf("MOV %s, %s\n", reg, t[i].op1);
        }
        else{
            printf("MOV %s, %s\n", reg, t[i].op1);
            switch(t[i].op){
                case '+':
                printf("ADD %s, %s\n", reg, t[i].op2);
                break;
                case '-':
                printf("SUB %s, %s\n", reg, t[i].op2);
                break;
                case '/':
                printf("DIV %s, %s\n", reg, t[i].op2);
                break;
                case '*':
                printf("MUL %s, %s\n", reg, t[i].op2);
                break;
                default:
                printf("INVALID");
                break;
            }
        }
        printf("MOV %s, %s\n", t[i].lhs, reg);
    }
}