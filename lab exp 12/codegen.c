#include <stdio.h>
#include <string.h>

char input[20];

// Function to generate assembly-like code
void generateCode(char op, char op1, char op2) {
    printf("MOV R0, %c\n", op1);

    switch(op) {
        case '+':
            printf("ADD R0, %c\n", op2);
            break;
        case '-':
            printf("SUB R0, %c\n", op2);
            break;
        case '*':
            printf("MUL R0, %c\n", op2);
            break;
        case '/':
            printf("DIV R0, %c\n", op2);
            break;
    }

    printf("MOV T, R0\n\n");
}

int main() {
    printf("Enter expression (e.g., a+b*c): ");
    scanf("%s", input);

    int len = strlen(input);

    printf("\nGenerated Code:\n");

    for(int i = 0; i < len; i++) {
        if(input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') {
            generateCode(input[i], input[i-1], input[i+1]);
        }
    }

    return 0;
}