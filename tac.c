#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define max 10 

char stack[max], tacstack[max][max], lhs, infix[max], postfix[max];
int top = -1, tcount = 0;

int prec(char sym) {
    if (sym == '^') return 3;
    if (sym == '*' || sym == '/') return 2;
    if (sym == '+' || sym == '-') return 1;
    return -1;
}

void infixtopostfix(){
  int k = 0;
  for(int i = 0; infix[i]; i++){
    char c = infix[i];
    if(isalpha(c)){
      postfix[k++] = c;
    }
    else{
      if(c == '('){
        stack[++top] = c;
      }
      else{
        if(c == ')'){
          while(top != -1 && stack[top] != '('){
            postfix[k++] = stack[top--];
          }
          top--;
        }
        else if(top != -1 && prec(stack[top]) >= prec(c)){
          while(top != -1 && prec(stack[top]) >= prec(c)){
            postfix[k++] = stack[top--];
          }
          stack[++top] = c;
        }
        else stack[++top] = c;
      }
    }
  }
  while(top != -1){
    postfix[k++] = stack[top--];
  }
  postfix[k] = '\0';
}

void tac(){
  for(int i = 0; postfix[i]; i++){
    char c = postfix[i];
    if(isalpha(c)){
      char temp[2] = {c, '\0'};
      strcpy(tacstack[++top], temp);
    }
    else{
      char a[max], b[max], t[max];
      strcpy(b, tacstack[top--]);
      strcpy(a, tacstack[top]);
      sprintf(t, "t%d", ++tcount);
      printf("%s = %s %c %s\n", t, a, c, b);
      strcpy(tacstack[top], t);
    }
  }
  printf("%c = %s\n", lhs, tacstack[0]);
}

void main(){
  printf("Enter the expression : ");
  scanf("%s", infix);
  lhs = infix[0];
  strcpy(infix, infix + 2);
  infixtopostfix();
  printf("postfix : %s\n", postfix);
  tac();
}