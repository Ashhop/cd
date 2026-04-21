#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 10

char productions[MAX][20];
char first[MAX][10], follow[MAX][10];
int n;

// Function to find FIRST
void findFirst(char c, int index) {
    for(int i = 0; i < n; i++) {
        if(productions[i][0] == c) {
            char *rhs = productions[i] + 3;

            // If terminal
            if(!isupper(rhs[0])) {
                int len = strlen(first[index]);
                first[index][len] = rhs[0];
                first[index][len+1] = '\0';
            }
            else {
                findFirst(rhs[0], index);
            }
        }
    }
}

// Function to find FOLLOW
void findFollow(char c, int index) {
    if(productions[0][0] == c) {
        strcat(follow[index], "$"); // Start symbol
    }

    for(int i = 0; i < n; i++) {
        char *rhs = productions[i] + 3;

        for(int j = 0; j < strlen(rhs); j++) {
            if(rhs[j] == c) {
                // If next symbol exists
                if(rhs[j+1] != '\0') {
                    if(!isupper(rhs[j+1])) {
                        int len = strlen(follow[index]);
                        follow[index][len] = rhs[j+1];
                        follow[index][len+1] = '\0';
                    }
                    else {
                        findFirst(rhs[j+1], index);
                    }
                }
                else {
                    // At end, add FOLLOW of LHS
                    if(productions[i][0] != c) {
                        findFollow(productions[i][0], index);
                    }
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

    // FIRST
    for(int i = 0; i < n; i++) {
        findFirst(productions[i][0], i);
    }

    // FOLLOW
    for(int i = 0; i < n; i++) {
        findFollow(productions[i][0], i);
    }

    printf("\nFIRST sets:\n");
    for(int i = 0; i < n; i++) {
        printf("FIRST(%c) = { %s }\n", productions[i][0], first[i]);
    }

    printf("\nFOLLOW sets:\n");
    for(int i = 0; i < n; i++) {
        printf("FOLLOW(%c) = { %s }\n", productions[i][0], follow[i]);
    }

    return 0;
}