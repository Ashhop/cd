#include <stdio.h>
#include <string.h>

char input[20];
int temp = 1;

// Function to generate Quadruple
void quadruple(char op, char op1, char op2) {
    printf("( %c , %c , %c , t%d )\n", op, op1, op2, temp);
}

// Function to generate Triple
void triple(char op, char op1, char op2, int index) {
    printf("%d : ( %c , %c , %c )\n", index, op, op1, op2);
}

// Function to generate Indirect Triple
void indirectTriple(int index) {
    printf("Pointer -> %d\n", index);
}

int main() {
    printf("Enter expression (e.g., a+b*c): ");
    scanf("%s", input);

    int len = strlen(input);

    printf("\nQuadruple Representation:\n");
    for(int i = 0; i < len; i++) {
        if(input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') {
            quadruple(input[i], input[i-1], input[i+1]);
            temp++;
        }
    }

    printf("\nTriple Representation:\n");
    int index = 0;
    for(int i = 0; i < len; i++) {
        if(input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') {
            triple(input[i], input[i-1], input[i+1], index++);
        }
    }

    printf("\nIndirect Triple Representation:\n");
    for(int i = 0; i < index; i++) {
        indirectTriple(i);
    }

    return 0;
}