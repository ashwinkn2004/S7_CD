#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define max 10

struct tac {
    char lhs[max], op1[max], op, op2[max];
} t[max];

void main() {
    int limit, constCount = 0;
    int val[max];
    char var[max][max];

    printf("Enter the total input: ");
    scanf("%d", &limit);

    printf("Enter the TAC:\n");
    for (int i = 0; i < limit; i++) {
        scanf("%s = %s %c %s", t[i].lhs, t[i].op1, &t[i].op, t[i].op2);
    }

    for (int i = 0; i < limit; i++) {
        // Replace constants if already known
        for (int j = 0; j < constCount; j++) {
            if (strcmp(var[j], t[i].op1) == 0)
                sprintf(t[i].op1, "%d", val[j]);
            if (strcmp(var[j], t[i].op2) == 0)
                sprintf(t[i].op2, "%d", val[j]);
        }

        int res = 0, isconst = 0;
        int v1 = atoi(t[i].op1);
        int v2 = (t[i].op2[0] != '_') ? atoi(t[i].op2) : 0;

        switch (t[i].op) {
            case '+': res = v1 + v2; isconst = 1; break;
            case '-': res = v1 - v2; isconst = 1; break;
            case '*': res = v1 * v2; isconst = 1; break;
            case '/': if (v2 != 0) { res = v1 / v2; isconst = 1; } break;
            case '_': res = v1; isconst = 1; break;
            default: printf("INVALID\n"); break;
        }

        if (isconst) {
            strcpy(var[constCount], t[i].lhs);
            val[constCount++] = res;
            sprintf(t[i].op1, "%d", res);
            t[i].op = '_';
            strcpy(t[i].op2, "_");
        }
    }

    printf("\nAfter Constant Propagation:\n");
    for (int i = 0; i < limit; i++) {
        printf("%s = %s", t[i].lhs, t[i].op1);
        if (t[i].op != '_')
            printf(" %c %s", t[i].op, t[i].op2);
        printf("\n");
    }
}
