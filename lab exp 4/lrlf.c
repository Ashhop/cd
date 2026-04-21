#include <stdio.h>
#include <string.h>

#define MAX 10
#define LEN 50

// Remove immediate left recursion
void removeLeftRecursion(char prod[10][LEN], int n) {
    char alpha[MAX][LEN], beta[MAX][LEN];
    int a = 0, b = 0;
    char nonTerm = prod[0][0];

    for(int i = 0; i < n; i++) {
        if(prod[i][0] == nonTerm && prod[i][1] == '-') {
            char *rhs = strchr(prod[i], '>') + 1;

            if(rhs[0] == nonTerm) {
                strcpy(alpha[a++], rhs + 1); // remove A
            } else {
                strcpy(beta[b++], rhs);
            }
        }
    }

    if(a == 0) {
        printf("No Left Recursion\n");
        return;
    }

    printf("\nAfter Removing Left Recursion:\n");
    printf("%c -> ", nonTerm);
    for(int i = 0; i < b; i++) {
        printf("%s%c' ", beta[i], nonTerm);
        if(i != b-1) printf("| ");
    }

    printf("\n%c' -> ", nonTerm);
    for(int i = 0; i < a; i++) {
        printf("%s%c' ", alpha[i], nonTerm);
        if(i != a-1) printf("| ");
    }
    printf("| ε\n");
}

// Left factoring
void leftFactoring(char prod[10][LEN], int n) {
    char prefix[LEN];
    strcpy(prefix, prod[0] + 3); // RHS of first production

    for(int i = 1; i < n; i++) {
        char *rhs = prod[i] + 3;
        int j = 0;
        while(prefix[j] && rhs[j] && prefix[j] == rhs[j]) {
            j++;
        }
        prefix[j] = '\0';
    }

    if(strlen(prefix) == 0) {
        printf("\nNo Left Factoring needed\n");
        return;
    }

    printf("\nAfter Left Factoring:\n");
    printf("%c -> %s%c'\n", prod[0][0], prefix, prod[0][0]);
    printf("%c' -> ", prod[0][0]);

    for(int i = 0; i < n; i++) {
        char *rhs = prod[i] + 3;
        if(strlen(rhs) == strlen(prefix))
            printf("ε ");
        else
            printf("%s ", rhs + strlen(prefix));
        if(i != n-1) printf("| ");
    }
    printf("\n");
}

int main() {
    int n;

    printf("Enter number of productions: ");
    scanf("%d", &n);

    char prod[10][LEN];
    printf("Enter productions (e.g., A->Aa or A->b):\n");

    for(int i = 0; i < n; i++) {
        scanf("%s", prod[i]);
    }

    removeLeftRecursion(prod, n);
    leftFactoring(prod, n);

    return 0;
}