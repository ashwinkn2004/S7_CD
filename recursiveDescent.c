/*
     E->TE'
     E'->+TE'|e
     T->FT'
     T'->*FT'|e
     F->(E)|id
*/

#include<stdio.h>

void E();
void EPRIME();
void T();
void TPRIME();
void F();

char input[50];
int i = 0, error = 0;

void E(){
    T();
    EPRIME();
}

void EPRIME(){
    if(input[i] == '+'){
        i++;
        T();
        EPRIME();
    }
}

void T(){
    F();
    TPRIME();
}

void TPRIME(){
    if(input[i] == '*'){
        i++;
        F();
        TPRIME();
    }
}

void F(){
    if(input[i] == 'i' && input[i+1] == 'd'){
        i += 2;
    }
    else{
        if(input[i] == '('){
            i++;
            E();
            if(input[i] == ')'){
                i++;
            }
            else error = 1;
        }
        else error = 1;
    }
    
}

void main(){
    printf("Enter the expression ends with $ : ");
    scanf("%s", input);
    E();
    if(error == 0 && input[i] == '$'){
        printf("Valid");
    }
    else{
        printf("Invalid");
    }
}