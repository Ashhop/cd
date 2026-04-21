#include <stdio.h>
#include <ctype.h>
#include <string.h>

char keywords[10][10] = {
    "int", "float", "if", "else", "while",
    "for", "char", "double", "return", "void"
};

int isKeyword(char *word) {
    for(int i = 0; i < 10; i++) {
        if(strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int main() {
    char input[100], token[50];
    int i = 0, j = 0;

    printf("Enter a line of code:\n");
    fgets(input, sizeof(input), stdin);

    while(input[i] != '\0') {

        // Skip spaces
        if(isspace(input[i])) {
            i++;
            continue;
        }

        // Identifier or Keyword
        if(isalpha(input[i])) {
            j = 0;
            while(isalnum(input[i])) {
                token[j++] = input[i++];
            }
            token[j] = '\0';

            if(isKeyword(token))
                printf("%s : Keyword\n", token);
            else
                printf("%s : Identifier\n", token);
        }

        // Number
        else if(isdigit(input[i])) {
            j = 0;
            while(isdigit(input[i])) {
                token[j++] = input[i++];
            }
            token[j] = '\0';
            printf("%s : Number\n", token);
        }

        // Operators
        else if(strchr("+-*/=<>", input[i])) {
            printf("%c : Operator\n", input[i]);
            i++;
        }

        // Special Symbols
        else if(strchr(";,(){}", input[i])) {
            printf("%c : Special Symbol\n", input[i]);
            i++;
        }

        else {
            printf("%c : Unknown\n", input[i]);
            i++;
        }
    }

    return 0;
}

