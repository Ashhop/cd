#include <stdio.h>
#include <string.h>
#include <ctype.h>

char expr[50];

int isOperator(char c) {
    return (c=='+' || c=='-' || c=='*' || c=='/');
}

// Function to evaluate simple expression like 2+3
int evaluate(int a, int b, char op) {
    switch(op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0;
}

int main() {
    printf("Enter expression (e.g., 2+3*4): ");
    scanf("%s", expr);

    int len = strlen(expr);

    printf("\nOptimized Expression:\n");

    for(int i = 0; i < len; i++) {
        if(isdigit(expr[i]) && isOperator(expr[i+1]) && isdigit(expr[i+2])) {
            int a = expr[i] - '0';
            int b = expr[i+2] - '0';
            char op = expr[i+1];

            int result = evaluate(a, b, op);
            printf("%d", result);

            i += 2; // skip processed part
        }
        else {
            printf("%c", expr[i]);
        }
    }

    return 0;
}