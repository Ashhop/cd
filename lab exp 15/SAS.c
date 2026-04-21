#include <stdio.h>
#include <string.h>

#define MAX 10

char stack[MAX][20];
int top = -1;

// Push function (allocate)
void push(char func[]) {
    if(top == MAX - 1) {
        printf("Stack Overflow\n");
        return;
    }
    strcpy(stack[++top], func);
    printf("Function %s called (pushed to stack)\n", func);
}

// Pop function (deallocate)
void pop() {
    if(top == -1) {
        printf("Stack Underflow\n");
        return;
    }
    printf("Function %s returned (popped from stack)\n", stack[top--]);
}

// Display stack
void display() {
    printf("\nCurrent Stack:\n");
    for(int i = top; i >= 0; i--) {
        printf("%s\n", stack[i]);
    }
}

int main() {
    int choice;
    char func[20];

    while(1) {
        printf("\n1. Function Call\n2. Function Return\n3. Display Stack\n4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter function name: ");
                scanf("%s", func);
                push(func);
                break;

            case 2:
                pop();
                break;

            case 3:
                display();
                break;

            case 4:
                return 0;

            default:
                printf("Invalid choice\n");
        }
    }
}