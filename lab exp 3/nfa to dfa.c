#include <stdio.h>
#include <string.h>

#define MAX 10

int nfa[MAX][2][MAX];   // NFA transitions
int nfa_count[MAX][2];  // Number of transitions

int dfa[MAX][2][MAX];
int dfa_count[MAX][2];

int dfa_states[MAX][MAX];
int dfa_state_count = 0;

// Check if state already exists
int exists(int *state, int size) {
    for(int i = 0; i < dfa_state_count; i++) {
        int match = 1;
        for(int j = 0; j < size; j++) {
            if(dfa_states[i][j] != state[j]) {
                match = 0;
                break;
            }
        }
        if(match) return i;
    }
    return -1;
}

// Add new DFA state
int add_state(int *state, int size) {
    for(int i = 0; i < size; i++)
        dfa_states[dfa_state_count][i] = state[i];
    return dfa_state_count++;
}

int main() {
    int n, t;

    printf("Enter number of NFA states: ");
    scanf("%d", &n);

    // Input transitions
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 2; j++) {
            printf("Number of transitions from state %d on input %d: ", i, j);
            scanf("%d", &t);
            nfa_count[i][j] = t;

            printf("Enter states: ");
            for(int k = 0; k < t; k++) {
                scanf("%d", &nfa[i][j][k]);
            }
        }
    }

    int start[MAX] = {0}; // initial state
    add_state(start, 1);

    for(int i = 0; i < dfa_state_count; i++) {
        for(int j = 0; j < 2; j++) {

            int temp[MAX], count = 0;

            for(int k = 0; k < MAX && dfa_states[i][k] != 0; k++) {
                int s = dfa_states[i][k];

                for(int m = 0; m < nfa_count[s][j]; m++) {
                    temp[count++] = nfa[s][j][m];
                }
            }

            int index = exists(temp, count);
            if(index == -1) {
                index = add_state(temp, count);
            }

            dfa[i][j][0] = index;
            dfa_count[i][j] = 1;
        }
    }

    printf("\nDFA Transition Table:\n");
    for(int i = 0; i < dfa_state_count; i++) {
        printf("State %d:\n", i);
        for(int j = 0; j < 2; j++) {
            printf("  on %d -> %d\n", j, dfa[i][j][0]);
        }
    }

    return 0;
}