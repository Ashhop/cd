#include <stdio.h>
#include <string.h>

#define MAX 20

struct node {
    char op;
    char left[5];
    char right[5];
    char result[5];
} dag[MAX];

int count = 0;

// Check if same operation already exists
int findNode(char op, char *left, char *right) {
    for(int i = 0; i < count; i++) {
        if(dag[i].op == op &&
           strcmp(dag[i].left, left) == 0 &&
           strcmp(dag[i].right, right) == 0) {
            return i;
        }
    }
    return -1;
}

int main() {
    int n;
    char op, left[5], right[5], result[5];

    printf("Enter number of expressions: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        printf("\nEnter expression (format: result = op1 op op2): ");
        scanf("%s = %s %c %s", result, left, &op, right);

        int index = findNode(op, left, right);

        if(index != -1) {
            printf("Common subexpression found! Reusing %s\n", dag[index].result);
        }
        else {
            dag[count].op = op;
            strcpy(dag[count].left, left);
            strcpy(dag[count].right, right);
            strcpy(dag[count].result, result);
            count++;
        }
    }

    printf("\nDAG Representation:\n");
    for(int i = 0; i < count; i++) {
        printf("%s = %s %c %s\n",
               dag[i].result,
               dag[i].left,
               dag[i].op,
               dag[i].right);
    }

    return 0;
}