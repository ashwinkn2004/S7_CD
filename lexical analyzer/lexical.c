#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

FILE *fp, *fpSym;
int count = 0;

int isRelop(char c) {
    return (c == '<' || c == '>' || c == '=' || c == '!');
}

int isBinop(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

void clear(char s[26]) {
    for (int i = 0; i < strlen(s); i++)
        s[i] = '\0';
}

int findSymbol(char s[26]) {
    char type[26], name[26];
    fseek(fpSym, 0, SEEK_SET);

    while (fscanf(fpSym, "%s %s", type, name) == 2) {
        if (strcmp(name, s) == 0) {
            if (strcmp(type, "id") == 0)
                printf("%s - identifier, %d\n", s, count);
            else
                printf("%s - %s\n", s, type);
            return 1;
        }
    }
    return 0;
}

void addSymbol(char s[26]) {
    fprintf(fpSym, "id %s\n", s);
    printf("%s - identifier, %d\n", s, count);
    count++;
}

void main() {
    fp = fopen("C:\\Users\\MY PC\\OneDrive\\Desktop\\NETWORK_LAB\\lexical analyzer\\input.c", "r");
    fpSym = fopen("symbol.txt", "a+");

    char c, token[26], lib[26];
    int state = 0, i = 0;

    while ((c = fgetc(fp)) != EOF) {
        switch (state) {
        case 0:
            if (isalpha(c)) {
                token[i++] = c;
                state = 1;
            } else if (isdigit(c)) {
                token[i++] = c;
                state = 2;
            } else if (isRelop(c)) {
                token[i++] = c;
                state = 3;
            } else if (isBinop(c)) {
                token[i++] = c;
                state = 4;
            } else if (c == '#') {
                state = 5;
            }
            break;

        case 1:
            if (isalnum(c)) {
                token[i++] = c;
            } else {
                token[i] = '\0';
                if (!findSymbol(token))
                    addSymbol(token);
                fseek(fp, -1L, SEEK_CUR);
                clear(token);
                i = 0;
                state = 0;
            }
            break;

        case 2:
            if (isdigit(c)) {
                token[i++] = c;
            } else {
                token[i] = '\0';
                printf("%s - Number\n", token);
                fseek(fp, -1L, SEEK_CUR);
                clear(token);
                i = 0;
                state = 0;
            }
            break;

        case 3:
            token[i] = '\0';
            printf("%s - Relop\n", token);
            clear(token);
            i = 0;
            state = 0;
            break;

        case 4:
            token[i] = '\0';
            printf("%s - Binop\n", token);
            clear(token);
            i = 0;
            state = 0;
            break;

        case 5:
            i = 0;
            while (c != ' ' && c != '\n' && c != EOF) {
                token[i++] = c;
                c = fgetc(fp);
            }
            token[i] = '\0';
            fscanf(fp, "%s", lib);

            if (strcmp(token, "include") == 0) {
                printf("include - Preprocessor Directive\n");
                printf("%s - Library\n", lib);
                fprintf(fpSym, "preprocessor include\n");
                fprintf(fpSym, "library %s\n", lib);
            }

            clear(token);
            clear(lib);
            state = 0;
            break;
        }
    }

    fclose(fp);
    fclose(fpSym);
}
