#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define MAX 10
#define LEN 20

char lhs, infix[LEN], postfix[LEN], stack[MAX], tacstack[MAX][MAX];
int top = -1, tcount = 0, qcount = -1;

struct quad {
    char op, arg1[MAX], arg2[MAX], res[MAX];
} q[MAX];
int prec(char sym) {
    if (sym == '^') return 3;
    if (sym == '*' || sym == '/') return 2;
    if (sym == '+' || sym == '-') return 1;
    return -1;
}
void infixtopostfix() {
    int k = 0;
    for (int i = 0; infix[i]; i++) {
        char c = infix[i];
        if (isalpha(c))
            postfix[k++] = c;
        else {
            if (c == '(')
                stack[++top] = c;
            else if (c == ')') {
                while (top != -1 && stack[top] != '(') {
                    postfix[k++] = stack[top--];
                }
                top--;
            } 
            else if (top != -1 && prec(stack[top]) >= prec(c)) {
                while (top != -1 && prec(stack[top]) >= prec(c)) {
                    postfix[k++] = stack[top--];
                }
                stack[++top] = c;
            }
            else
                stack[++top] = c;
        }
    }
    while (top != -1) {
        postfix[k++] = stack[top--];
    }
    postfix[k] = '\0';
}
void tac() {
    for (int i = 0; postfix[i]; i++) {
        char c = postfix[i];
        if (isalpha(c)) {
            char temp[2] = {c, '\0'};
            strcpy(tacstack[++top], temp);
        } 
        else {
            char a[MAX], b[MAX], t[MAX];
            strcpy(b, tacstack[top--]);
            strcpy(a, tacstack[top]);
            sprintf(t, "t%d", ++tcount);
            printf("%s = %s %c %s\n", t, a, c, b);
            strcpy(tacstack[top], t);
            q[++qcount].op = c;
            strcpy(q[qcount].arg1, a);
            strcpy(q[qcount].arg2, b);
            strcpy(q[qcount].res, t);
        }
    }
    printf("%c = %s\n", lhs, tacstack[0]);
    q[++qcount].op = '=';
    strcpy(q[qcount].arg1, tacstack[0]);
    strcpy(q[qcount].arg2, "-");
    sprintf(q[qcount].res, "%c", lhs);
}
void triple() {
    for (int i = 0; i <= qcount; i++) {
        printf("[%d]\t%c\t", i, q[i].op);
        if (q[i].arg1[0] == 't')
            printf("[%d]\t", atoi(q[i].arg1 + 1) - 1);
        else
            printf("%s\t", q[i].arg1);
        if (q[i].arg2[0] == 't')
            printf("[%d]\n", atoi(q[i].arg2 + 1) - 1);
        else
            printf("%s\n", q[i].arg2);
    }
}
void main() {
    printf("Enter the expression : ");
    scanf("%s", infix);
    lhs = infix[0];
    strcpy(infix, infix + 2);
    infixtopostfix();
    printf("\nPostfix expression : %s\n\nThree address code : \n", postfix);
    tac();
    printf("\nQuadruple representation : \nNo.\top\targ1\targ2\tres\n");
    for (int i = 0; i <= qcount; i++) {
        printf("[%d]\t%c\t%s\t%s\t%s\n", i, q[i].op, q[i].arg1, q[i].arg2, q[i].res);
    }
    printf("\nTriple representation : \nNo.\top\targ1\targ2\n");
    triple();
}