#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 10

char productions[MAX][20];
int n;

// Function to display item with dot
void addDot(char *prod) {
    char temp[20];
    strcpy(temp, prod);

    // Insert dot after ->
    int i;
    for(i = 0; temp[i] != '>'; i++);

    printf("%.*s.%s\n", i+1, temp, temp+i+1);
}

// Function to find closure
void closure(char *prod) {
    addDot(prod);

    // Find symbol after dot
    char *arrow = strstr(prod, "->");
    char next = arrow[2];

    // If non-terminal, expand
    if(isupper(next)) {
        for(int i = 0; i < n; i++) {
            if(productions[i][0] == next) {
                closure(productions[i]);
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

    printf("\nLR(0) Items:\n");

    for(int i = 0; i < n; i++) {
        closure(productions[i]);
        printf("\n");
    }

    return 0;
}