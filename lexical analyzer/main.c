#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

FILE *fp;

int isKeyword(char *arr){
    char *keys[] = {
        "int","float","void","main","return"
    };
    for(int i = 0; i < 5; i++){
        if(strcmp(arr, keys[i]) == 0){
            return 1;
        }
    }
    return 0;
}

void main(){
    fp = fopen("C:\\Users\\MY PC\\OneDrive\\Desktop\\NETWORK_LAB\\lexical analyzer\\input.c", "r");
    char ch, arr[200], j = 0;
    while((ch = fgetc(fp)) != EOF){
        if(ch == '#'){
            arr[j++] = ch;
            while(isalpha((ch = fgetc(fp)))){
                arr[j++] = ch;
            }
            arr[j] = '\0';
            j = 0;
            ungetc(ch, fp);
            printf("%s - preprocessor directive\n", arr);
            strcpy(arr, "");
        }
        else if(ch == '<'){
            arr[j++] = ch;
            while((ch = fgetc(fp)) != '>'){
                arr[j++] = ch;
            }
            arr[j++] = ch;
            arr[j] = '\0';
            j = 0;
            printf("%s - library\n", arr);
            strcpy(arr, "");
        }
        else if(isalpha(ch)){
            arr[j++] = ch;
            while(isalnum(ch = fgetc(fp))){
                arr[j++] = ch;
            }
            arr[j] = '\0';
            j = 0;
            ungetc(ch, fp);
            printf("%s - %s\n", arr, isKeyword(arr) ? "keyword" : "identifier");
            strcpy(arr, "");
        }
        else if(isdigit(ch)){
            arr[j++] = ch;
            while(isdigit(ch = fgetc(fp))){
                arr[j++] = ch;
            }
            arr[j] = '\0';
            j = 0;
            ungetc(ch, fp);
            printf("%s - Number\n", arr);
            strcpy(arr, "");
        }
        else if(isspace(ch)){
            continue;
        }
        else{
            switch(ch){
                case '=': printf("= - Relational operator\n"); break;
                case ';':
                case ',': printf("%c - Separator\n", ch); break;
                case '(':
                case ')':
                case '{':
                case '}': printf("%c - Delimiter\n", ch); break;
            }
        }
    }
}
