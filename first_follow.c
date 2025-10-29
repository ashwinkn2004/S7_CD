#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 20

char productions[20][20];
char nonTerminals[20];
int n, ntCount = 0;

void FIRST(char[], char);
void FOLLOW(char[], char);
void addToSet(char[], char);
int isNT(char);
void trimSpaces(char*);

int main() {
    char result[SIZE];
    printf("Enter number of productions: ");
    scanf("%d", &n); 
    
    printf("Enter productions:\n");
    for (int i = 0; i < n; i++) 
    {
        scanf("%s", productions[i]);
        trimSpaces(productions[i]);

        // collect unique non-terminals
        int exists = 0;
        for (int j = 0; j < ntCount; j++)
            if (nonTerminals[j] == productions[i][0]) exists = 1;
        if (!exists) nonTerminals[ntCount++] = productions[i][0];
    }

    printf("\n");
    for (int i = 0; i < n; i++) printf("%s\n", productions[i]);
    printf("\n");

    for (int i = 0; i < ntCount; i++) {
        strcpy(result, "");
        FIRST(result, nonTerminals[i]);
        printf("First(%c) = {", nonTerminals[i]);
        for (int j = 0; result[j]; j++)
            printf("%c%s", result[j], result[j + 1] ? ", " : "");
        printf(",}\n\n");
    }

    for (int i = 0; i < ntCount; i++) {
        strcpy(result, "");
        FOLLOW(result, nonTerminals[i]);
        printf("Follow(%c) = {", nonTerminals[i]);
        for (int j = 0; result[j]; j++)
            printf("%c%s", result[j], result[j + 1] ? ", " : "");
        printf(",}\n\n");
    }
    return 0;
}

void trimSpaces(char* str) {
    int k = 0;
    for (int i = 0; str[i]; i++)
        if (str[i] != ' ') str[k++] = str[i];
    str[k] = '\0';
}

void addToSet(char res[], char c) {
    if (!strchr(res, c)) {
        int len = strlen(res);
        res[len] = c;
        res[len + 1] = '\0';
    }
}

int isNT(char c) { return isupper(c); }

void FIRST(char res[], char c) {
    if (!isNT(c) && c != '#') { addToSet(res, c); return; }

    for (int i = 0; i < n; i++) {
        if (productions[i][0] != c) continue;
        if (productions[i][2] == '#') addToSet(res, '#');
        else {
            int k = 2, eps = 1;
            while (productions[i][k] && eps) {
                char next = productions[i][k++];
                char temp[SIZE] = "";
                FIRST(temp, next);
                for (int j = 0; temp[j]; j++)
                    if (temp[j] != '#') addToSet(res, temp[j]);
                eps = strchr(temp, '#') != NULL;
            }
            if (eps) addToSet(res, '#');
        }
    }
}

void FOLLOW(char res[], char c) {
    if (productions[0][0] == c) addToSet(res, '$');

    for (int i = 0; i < n; i++) {
        for (int j = 2; productions[i][j]; j++) {
            if (productions[i][j] != c) continue;

            int k = j + 1, eps = 1;
            while (productions[i][k] && eps) {
                char next = productions[i][k++];
                if (!isNT(next) && next != '#') { addToSet(res, next); eps = 0; break; }

                char temp[SIZE] = "";
                FIRST(temp, next);
                for (int m = 0; temp[m]; m++)
                    if (temp[m] != '#') addToSet(res, temp[m]);
                eps = strchr(temp, '#') != NULL;
            }
            if (eps && productions[i][0] != c) {
                char tempFollow[SIZE] = "";
                FOLLOW(tempFollow, productions[i][0]);
                for (int m = 0; tempFollow[m]; m++)
                    addToSet(res, tempFollow[m]);
            }
        }
    }
}