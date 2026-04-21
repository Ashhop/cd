#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

int state = 1;

typedef struct {
    int start, end;
} NFA;

NFA stack[MAX];
int top = -1;

// Push to stack
void push(NFA n) {
    stack[++top] = n;
}

// Pop from stack
NFA pop() {
    return stack[top--];
}

// Create basic NFA for symbol
NFA create_nfa(char symbol) {
    NFA n;
    n.start = state++;
    n.end = state++;

    printf("%d -- %c --> %d\n", n.start, symbol, n.end);
    return n;
}

// Concatenation
NFA concat(NFA n1, NFA n2) {
    printf("%d -- ε --> %d\n", n1.end, n2.start);
    n1.end = n2.end;
    return n1;
}

// Union
NFA union_nfa(NFA n1, NFA n2) {
    NFA n;
    n.start = state++;
    n.end = state++;

    printf("%d -- ε --> %d\n", n.start, n1.start);
    printf("%d -- ε --> %d\n", n.start, n2.start);
    printf("%d -- ε --> %d\n", n1.end, n.end);
    printf("%d -- ε --> %d\n", n2.end, n.end);

    return n;
}

// Kleene star
NFA kleene(NFA n1) {
    NFA n;
    n.start = state++;
    n.end = state++;

    printf("%d -- ε --> %d\n", n.start, n1.start);
    printf("%d -- ε --> %d\n", n.start, n.end);
    printf("%d -- ε --> %d\n", n1.end, n1.start);
    printf("%d -- ε --> %d\n", n1.end, n.end);

    return n;
}

int main() {
    char regex[MAX];
    printf("Enter postfix regular expression:\n");
    scanf("%s", regex);

    for(int i = 0; i < strlen(regex); i++) {
        char ch = regex[i];

        if(ch == '*') {
            NFA n1 = pop();
            push(kleene(n1));
        }
        else if(ch == '.') {
            NFA n2 = pop();
            NFA n1 = pop();
            push(concat(n1, n2));
        }
        else if(ch == '|') {
            NFA n2 = pop();
            NFA n1 = pop();
            push(union_nfa(n1, n2));
        }
        else {
            push(create_nfa(ch));
        }
    }

    NFA result = pop();
    printf("\nStart State: %d\n", result.start);
    printf("Final State: %d\n", result.end);

    return 0;
}