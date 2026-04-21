#include <stdio.h>
#include <string.h>

char stack[50], input[50];
int top = -1;

void shift(char c) {
    stack[++top] = c;
    stack[top + 1] = '\0';
}

void reduce() {
    // Example grammar:
    // E -> E+E
    // E -> E*E
    // E -> (E)
    // E -> id

    if(strcmp(stack, "id") == 0) {
        strcpy(stack, "E");
        top = 0;
        printf("Reduce: E->id\n");
    }
    else if(strstr(stack, "E+E")) {
        char *pos = strstr(stack, "E+E");
        *pos = 'E';
        *(pos + 1) = '\0';
        top = strlen(stack) - 1;
        printf("Reduce: E->E+E\n");
    }
    else if(strstr(stack, "E*E")) {
        char *pos = strstr(stack, "E*E");
        *pos = 'E';
        *(pos + 1) = '\0';
        top = strlen(stack) - 1;
        printf("Reduce: E->E*E\n");
    }
    else if(strstr(stack, "(E)")) {
        char *pos = strstr(stack, "(E)");
        *pos = 'E';
        *(pos + 1) = '\0';
        top = strlen(stack) - 1;
        printf("Reduce: E->(E)\n");
    }
}

int main() {
    printf("Enter input string (use i for id): ");
    scanf("%s", input);

    int i = 0;
    stack[0] = '\0';

    printf("\nStack\tInput\tAction\n");

    while(1) {
        if(input[i] != '\0') {
            shift(input[i]);
            printf("%s\t%s\tShift\n", stack, input + i + 1);
            i++;
            reduce();
        }
        else {
            reduce();
            if(strcmp(stack, "E") == 0) {
                printf("%s\t\tAccepted\n", stack);
                break;
            }
            else {
                printf("%s\t\tRejected\n", stack);
                break;
            }
        }
    }

    return 0;
}