#include<stdio.h>
#include<string.h>
#include<ctype.h>

int getIndex(char c, char *terminals, int limit){
    for(int i = 0; i < limit; i++){
        if(c == terminals[i]){
            return i;
        }
    }
    return -1;
}

void main(){
    char terminals[10], table[10][10], input[50], stack[10];
    int top = 0, input_ptr = 0;
    printf("Enter the terminals : ");
    scanf("%s", terminals);
    
    int limit = strlen(terminals);
    
    printf("Enter the precedence table : \n");
    for(int i = 0; i < limit; i++){
        for(int j = 0; j < limit; j++){
            scanf(" %c", &table[i][j]);
        }
    }
    
    printf("Enter the input : ");
    scanf("%s", input);
    
    stack[0] = '$';
    stack[1] = '\0';
    
    printf("STACK\t\tINPUT\t\tACTION\n");
    printf("-----\t\t-----\t\t------\n");
    
    while(1){
        char stack_chr = stack[top];
        char input_chr = input[input_ptr];
        int stack_idx = getIndex(stack_chr, terminals, limit);
        int input_idx = getIndex(input_chr, terminals, limit);
        
        if(stack_idx == -1 || input_idx == -1){
            printf("Error\n");
            break;
        }
        
        if(stack_chr == '$' && input_chr == '$'){
            printf("%-15s %-15s Accepted!\n", stack, input + input_ptr);
            break;
        }
        
        char reln = table[stack_idx][input_idx];
        if(reln == '<' || reln == '='){
            printf("%-15s %-15s shift %c\n", stack, input + input_ptr, input_chr);
            stack[++top] = input_chr;
            stack[top+1] = '\0';
            input_ptr++;
        }
        else if(reln == '>'){
            printf("%-15s %-15s Reduce\n", stack, input + input_ptr);
            if(top == 0){
                printf("Nothing to reduce\n");
                break;
            }
            stack[top--] = '\0';
        }
        else{
            printf("Error\n");
            break;
        }
    }
}