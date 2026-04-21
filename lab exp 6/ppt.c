#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 10

char productions[MAX][10];
char first[MAX][10];
char follow[MAX][10];
char table[MAX][MAX][10];

int n;

// Find FIRST (simple version)
void findFirst(char c, int index) {
    if(!isupper(c)) {
        int len = strlen(first[index]);
        first[index][len] = c;
        first[index][len+1] = '\0';
        return;
    }

    for(int i = 0; i < n; i++) {
        if(productions[i][0] == c) {
            if(productions[i][2] == '#') {
                strcat(first[index], "#");
            } else {
                findFirst(productions[i][2], index);
            }
        }
    }
}

// Find FOLLOW (simple version)
void findFollow(char c, int index) {
    if(productions[0][0] == c) {
        strcat(follow[index], "$");
    }

    for(int i = 0; i < n; i++) {
        for(int j = 2; j < strlen(productions[i]); j++) {
            if(productions[i][j] == c) {

                if(productions[i][j+1] != '\0') {
                    char next = productions[i][j+1];

                    if(!isupper(next)) {
                        int len = strlen(follow[index]);
                        follow[index][len] = next;
                        follow[index][len+1] = '\0';
                    } else {
                        for(int k = 0; k < n; k++) {
                            if(productions[k][0] == next) {
                                strcat(follow[index], first[k]);
                            }
                        }
                    }
                } else {
                    if(productions[i][0] != c)
                        findFollow(productions[i][0], index);
                }
            }
        }
    }
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (use # for epsilon):\n");
    for(int i = 0; i < n; i++) {
        scanf("%s", productions[i]);
    }

    // Compute FIRST
    for(int i = 0; i < n; i++) {
        findFirst(productions[i][0], i);
    }

    // Compute FOLLOW
    for(int i = 0; i < n; i++) {
        findFollow(productions[i][0], i);
    }

    // Build parsing table
    for(int i = 0; i < n; i++) {
        char A = productions[i][0];
        char *rhs = productions[i] + 3;

        for(int j = 0; j < strlen(first[i]); j++) {
            if(first[i][j] != '#') {
                table[A - 'A'][first[i][j]] = productions[i];
            }
        }

        // If epsilon present
        if(strchr(first[i], '#')) {
            for(int j = 0; j < strlen(follow[i]); j++) {
                table[A - 'A'][follow[i][j]] = productions[i];
            }
        }
    }

    // Display table
    printf("\nPredictive Parsing Table:\n");
    for(int i = 0; i < n; i++) {
        printf("For %c:\n", productions[i][0]);
        for(int j = 0; j < 128; j++) {
            if(table[productions[i][0]-'A'][j] != NULL) {
                printf("  M[%c, %c] = %s\n", productions[i][0], j, table[productions[i][0]-'A'][j]);
            }
        }
    }

    return 0;
}