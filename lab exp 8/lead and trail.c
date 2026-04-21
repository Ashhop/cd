#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 10

char productions[MAX][10];
char leading[MAX][10], trailing[MAX][10];
int n;

// Function to compute LEADING
void findLeading(char c, int index) {
    for(int i = 0; i < n; i++) {
        if(productions[i][0] == c) {
            char *rhs = productions[i] + 3;

            // Case 1: first symbol is terminal
            if(!isupper(rhs[0])) {
                int len = strlen(leading[index]);
                leading[index][len] = rhs[0];
                leading[index][len+1] = '\0';
            }
            // Case 2: first symbol is non-terminal
            else {
                findLeading(rhs[0], index);

                // check second symbol
                if(rhs[1] != '\0' && !isupper(rhs[1])) {
                    int len = strlen(leading[index]);
                    leading[index][len] = rhs[1];
                    leading[index][len+1] = '\0';
                }
            }
        }
    }
}

// Function to compute TRAILING
void findTrailing(char c, int index) {
    for(int i = 0; i < n; i++) {
        if(productions[i][0] == c) {
            char *rhs = productions[i] + 3;
            int len_rhs = strlen(rhs);

            // Case 1: last symbol is terminal
            if(!isupper(rhs[len_rhs-1])) {
                int len = strlen(trailing[index]);
                trailing[index][len] = rhs[len_rhs-1];
                trailing[index][len+1] = '\0';
            }
            // Case 2: last symbol is non-terminal
            else {
                findTrailing(rhs[len_rhs-1], index);

                // check second last symbol
                if(len_rhs > 1 && !isupper(rhs[len_rhs-2])) {
                    int len = strlen(trailing[index]);
                    trailing[index][len] = rhs[len_rhs-2];
                    trailing[index][len+1] = '\0';
                }
            }
        }
    }
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (e.g., E->E+T):\n");
    for(int i = 0; i < n; i++) {
        scanf("%s", productions[i]);
    }

    // Compute LEADING
    for(int i = 0; i < n; i++) {
        findLeading(productions[i][0], i);
    }

    // Compute TRAILING
    for(int i = 0; i < n; i++) {
        findTrailing(productions[i][0], i);
    }

    // Print LEADING
    printf("\nLEADING sets:\n");
    for(int i = 0; i < n; i++) {
        printf("LEADING(%c) = { %s }\n", productions[i][0], leading[i]);
    }

    // Print TRAILING
    printf("\nTRAILING sets:\n");
    for(int i = 0; i < n; i++) {
        printf("TRAILING(%c) = { %s }\n", productions[i][0], trailing[i]);
    }

    return 0;
}
